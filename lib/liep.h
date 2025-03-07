#pragma once

#ifndef INIREADER_H
#define INIREADER_H

#include <map>
#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>

namespace inireader{
    const std::string defaultGroup = "default";

	// shortcuts
    using groupvalues = std::map<std::string, std::string>;
    using inigroups = std::map<std::string, groupvalues>;
    
    using initresult = std::pair<bool, inigroups>;

    /**
     * @brief allows you to initialize the file
     * 
     * @param loc localization of the file
     * @return initresult (std::pair<bool, inireader::inigroup). The first bool indicates whether it was successful
     */
    initresult initIniFile(const std::filesystem::path& loc);

    /**
     * @brief check if there was an error with inireader::initresult
     * it just checks the first bool
     * 
     * @param res inireader::iniresult reference
     * @return true in most of cases
     * @return false if there was an error
     */
    bool inline isIniError(const initresult& res);

    /**
     * @brief Get the Group object
     * 
     * @param res just inireader::initresult reference
     * @param groupName the name of the group
     * @return std::pair<bool, groupvalues> The first bool indicates whether it was successful
     */
    std::pair<bool, groupvalues> inline getGroup(const initresult& res, const std::string& groupName = defaultGroup);

    /**
     * @brief get the value that is under provided key
     * 
     * @param group iniresult::groupvalues reference
     * @param key the key
     * @return std::pair<bool, std::string> The first bool indicates whether it was successful
     */
    std::pair<bool, std::string> inline getValue(const groupvalues& group, const std::string& key);

    /**
     * @brief  get the value that is under provided key and group
     * 
     * @param res iniresult::groupvalues reference
     * @param groupName the name of the group
     * @param key the key
     * @return td::pair<bool, std::string> The first bool indicates whether it was successful
     */
    std::pair<bool, std::string> inline getValueQuick(const initresult& res, const std::string& key, const std::string& groupName = defaultGroup);


    /**
     * @brief allows you to merge results. Duplicates will be replaced. It defacto adds everything to first and returns that
     * 
     * @param first the priority result
     * @param second  the second result
     * @return initresult 
     */
    initresult inline mergeResults(initresult& first, initresult& second);

    /**
     * @brief allows you to merge results. Duplicates will be replaced. It defacto adds everything to first and returns that
     * 
     * @param first the priority result
     * @param second  the second result
     * @return initresult 
     */
    groupvalues inline mergeGroups(groupvalues& first, groupvalues& second);
}

#endif