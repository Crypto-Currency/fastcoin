// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "validationinterface.h"

#include <boost/bind/bind.hpp>

static CMainSignals g_signals;

CMainSignals& GetMainSignals()
{
    return g_signals;
}

void RegisterValidationInterface(CValidationInterface* pwalletIn) {
#if BOOST_VERSION >= 106000
    g_signals.UpdatedBlockTip.connect(boost::bind(&CValidationInterface::UpdatedBlockTip,
                                                  pwalletIn, boost::placeholders::_1,
                                                  boost::placeholders::_2,
                                                  boost::placeholders::_3));
    g_signals.SyncTransaction.connect(boost::bind(&CValidationInterface::SyncTransaction,
                                                  pwalletIn, boost::placeholders::_1,
                                                  boost::placeholders::_2,
                                                  boost::placeholders::_3));
    g_signals.UpdatedTransaction.connect(boost::bind(&CValidationInterface::UpdatedTransaction,
                                                     pwalletIn, boost::placeholders::_1));
    g_signals.SetBestChain.connect(boost::bind(&CValidationInterface::SetBestChain,
                                               pwalletIn, boost::placeholders::_1));
    g_signals.Inventory.connect(boost::bind(&CValidationInterface::Inventory,
                                            pwalletIn, boost::placeholders::_1));
    g_signals.Broadcast.connect(boost::bind(&CValidationInterface::ResendWalletTransactions,
                                            pwalletIn, boost::placeholders::_1, boost::placeholders::_2));
    g_signals.BlockChecked.connect(boost::bind(&CValidationInterface::BlockChecked,
                                               pwalletIn, boost::placeholders::_1,
                                               boost::placeholders::_2));
    g_signals.ScriptForMining.connect(boost::bind(&CValidationInterface::GetScriptForMining,
                                                  pwalletIn, boost::placeholders::_1));
    g_signals.BlockFound.connect(boost::bind(&CValidationInterface::ResetRequestCount,
                                             pwalletIn, boost::placeholders::_1));
    g_signals.NewPoWValidBlock.connect(boost::bind(&CValidationInterface::NewPoWValidBlock,
                                                   pwalletIn, boost::placeholders::_1,
                                                   boost::placeholders::_2));
#else
    g_signals.UpdatedBlockTip.connect(boost::bind(&CValidationInterface::UpdatedBlockTip,pwalletIn,_1,_2,_3));
    g_signals.SyncTransaction.connect(boost::bind(&CValidationInterface::SyncTransaction,pwalletIn,_1,_2,_3));
    g_signals.UpdatedTransaction.connect(boost::bind(&CValidationInterface::UpdatedTransaction,pwalletIn,_1));
    g_signals.SetBestChain.connect(boost::bind(&CValidationInterface::SetBestChain,pwalletIn,_1));
    g_signals.Inventory.connect(boost::bind(&CValidationInterface::Inventory,pwalletIn,_1));
    g_signals.Broadcast.connect(boost::bind(&CValidationInterface::ResendWalletTransactions,pwalletIn,_1,_2));
    g_signals.BlockChecked.connect(boost::bind(&CValidationInterface::BlockChecked,pwalletIn,_1,_2));
    g_signals.ScriptForMining.connect(boost::bind(&CValidationInterface::GetScriptForMining,pwalletIn,_1));
    g_signals.BlockFound.connect(boost::bind(&CValidationInterface::ResetRequestCount,pwalletIn,_1));
    g_signals.NewPoWValidBlock.connect(boost::bind(&CValidationInterface::NewPoWValidBlock,pwalletIn,_1,_2));
#endif
}

void UnregisterValidationInterface(CValidationInterface* pwalletIn) {
#if BOOST_VERSION >= 106000
    g_signals.BlockFound.disconnect(boost::bind(&CValidationInterface::ResetRequestCount,
                                                pwalletIn, boost::placeholders::_1));
    g_signals.ScriptForMining.disconnect(boost::bind(&CValidationInterface::GetScriptForMining,
                                                     pwalletIn, boost::placeholders::_1));
    g_signals.BlockChecked.disconnect(boost::bind(&CValidationInterface::BlockChecked,
                                                  pwalletIn, boost::placeholders::_1,
                                                  boost::placeholders::_2));
    g_signals.Broadcast.disconnect(boost::bind(&CValidationInterface::ResendWalletTransactions,
                                               pwalletIn, boost::placeholders::_1,
                                               boost::placeholders::_2));
    g_signals.Inventory.disconnect(boost::bind(&CValidationInterface::Inventory,
                                               pwalletIn, boost::placeholders::_1));
    g_signals.SetBestChain.disconnect(boost::bind(&CValidationInterface::SetBestChain,
                                                  pwalletIn, boost::placeholders::_1));
    g_signals.UpdatedTransaction.disconnect(boost::bind(&CValidationInterface::UpdatedTransaction,
                                                        pwalletIn, boost::placeholders::_1));
    g_signals.SyncTransaction.disconnect(boost::bind(&CValidationInterface::SyncTransaction,
                                                     pwalletIn, boost::placeholders::_1,
                                                     boost::placeholders::_2,
                                                     boost::placeholders::_3));
    g_signals.UpdatedBlockTip.disconnect(boost::bind(&CValidationInterface::UpdatedBlockTip,
                                         pwalletIn, boost::placeholders::_1,
                                         boost::placeholders::_2,
                                         boost::placeholders::_3));
    g_signals.NewPoWValidBlock.disconnect(boost::bind(&CValidationInterface::NewPoWValidBlock,
                                          pwalletIn, boost::placeholders::_1,
                                          boost::placeholders::_2));
#else
    g_signals.BlockFound.disconnect(boost::bind(&CValidationInterface::ResetRequestCount,pwalletIn,_1));
    g_signals.ScriptForMining.disconnect(boost::bind(&CValidationInterface::GetScriptForMining,pwalletIn,_1));
    g_signals.BlockChecked.disconnect(boost::bind(&CValidationInterface::BlockChecked,pwalletIn,_1,_2));
    g_signals.Broadcast.disconnect(boost::bind(&CValidationInterface::ResendWalletTransactions,pwalletIn,_1,_2));
    g_signals.Inventory.disconnect(boost::bind(&CValidationInterface::Inventory,pwalletIn,_1));
    g_signals.SetBestChain.disconnect(boost::bind(&CValidationInterface::SetBestChain,pwalletIn,_1));
    g_signals.UpdatedTransaction.disconnect(boost::bind(&CValidationInterface::UpdatedTransaction,pwalletIn,_1));
    g_signals.SyncTransaction.disconnect(boost::bind(&CValidationInterface::SyncTransaction,pwalletIn,_1,_2,_3));
    g_signals.UpdatedBlockTip.disconnect(boost::bind(&CValidationInterface::UpdatedBlockTip,pwalletIn,_1,_2,_3));
    g_signals.NewPoWValidBlock.disconnect(boost::bind(&CValidationInterface::NewPoWValidBlock,pwalletIn,_1,_2));
#endif
}

void UnregisterAllValidationInterfaces() {
    g_signals.BlockFound.disconnect_all_slots();
    g_signals.ScriptForMining.disconnect_all_slots();
    g_signals.BlockChecked.disconnect_all_slots();
    g_signals.Broadcast.disconnect_all_slots();
    g_signals.Inventory.disconnect_all_slots();
    g_signals.SetBestChain.disconnect_all_slots();
    g_signals.UpdatedTransaction.disconnect_all_slots();
    g_signals.SyncTransaction.disconnect_all_slots();
    g_signals.UpdatedBlockTip.disconnect_all_slots();
    g_signals.NewPoWValidBlock.disconnect_all_slots();
}
