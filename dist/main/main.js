module.exports =
/******/ (function(modules) { // webpackBootstrap
/******/ 	// eslint-disable-next-line no-unused-vars
/******/ 	function hotDownloadUpdateChunk(chunkId) {
/******/ 		var filename = require("path").join(__dirname, "" + chunkId + "." + hotCurrentHash + ".hot-update.js");
/******/ 		require("fs").readFile(filename, "utf-8", function(err, content) {
/******/ 			if (err) {
/******/ 				if (__webpack_require__.onError) return __webpack_require__.oe(err);
/******/ 				else throw err;
/******/ 			}
/******/ 			var chunk = {};
/******/ 			require("vm").runInThisContext(
/******/ 				"(function(exports) {" + content + "\n})",
/******/ 				{ filename: filename }
/******/ 			)(chunk);
/******/ 			hotAddUpdateChunk(chunk.id, chunk.modules);
/******/ 		});
/******/ 	}
/******/
/******/ 	// eslint-disable-next-line no-unused-vars
/******/ 	function hotDownloadManifest() {
/******/ 		var filename = require("path").join(__dirname, "" + hotCurrentHash + ".hot-update.json");
/******/ 		return new Promise(function(resolve, reject) {
/******/ 			require("fs").readFile(filename, "utf-8", function(err, content) {
/******/ 				if (err) return resolve();
/******/ 				try {
/******/ 					var update = JSON.parse(content);
/******/ 				} catch (e) {
/******/ 					return reject(e);
/******/ 				}
/******/ 				resolve(update);
/******/ 			});
/******/ 		});
/******/ 	}
/******/
/******/ 	//eslint-disable-next-line no-unused-vars
/******/ 	function hotDisposeChunk(chunkId) {
/******/ 		delete installedChunks[chunkId];
/******/ 	}
/******/
/******/ 	var hotApplyOnUpdate = true;
/******/ 	var hotCurrentHash = "7b38bec22c5a2160e296"; // eslint-disable-line no-unused-vars
/******/ 	var hotRequestTimeout = 10000;
/******/ 	var hotCurrentModuleData = {};
/******/ 	var hotCurrentChildModule; // eslint-disable-line no-unused-vars
/******/ 	var hotCurrentParents = []; // eslint-disable-line no-unused-vars
/******/ 	var hotCurrentParentsTemp = []; // eslint-disable-line no-unused-vars
/******/
/******/ 	// eslint-disable-next-line no-unused-vars
/******/ 	function hotCreateRequire(moduleId) {
/******/ 		var me = installedModules[moduleId];
/******/ 		if (!me) return __webpack_require__;
/******/ 		var fn = function(request) {
/******/ 			if (me.hot.active) {
/******/ 				if (installedModules[request]) {
/******/ 					if (installedModules[request].parents.indexOf(moduleId) === -1)
/******/ 						installedModules[request].parents.push(moduleId);
/******/ 				} else {
/******/ 					hotCurrentParents = [moduleId];
/******/ 					hotCurrentChildModule = request;
/******/ 				}
/******/ 				if (me.children.indexOf(request) === -1) me.children.push(request);
/******/ 			} else {
/******/ 				console.warn(
/******/ 					"[HMR] unexpected require(" +
/******/ 						request +
/******/ 						") from disposed module " +
/******/ 						moduleId
/******/ 				);
/******/ 				hotCurrentParents = [];
/******/ 			}
/******/ 			return __webpack_require__(request);
/******/ 		};
/******/ 		var ObjectFactory = function ObjectFactory(name) {
/******/ 			return {
/******/ 				configurable: true,
/******/ 				enumerable: true,
/******/ 				get: function() {
/******/ 					return __webpack_require__[name];
/******/ 				},
/******/ 				set: function(value) {
/******/ 					__webpack_require__[name] = value;
/******/ 				}
/******/ 			};
/******/ 		};
/******/ 		for (var name in __webpack_require__) {
/******/ 			if (
/******/ 				Object.prototype.hasOwnProperty.call(__webpack_require__, name) &&
/******/ 				name !== "e"
/******/ 			) {
/******/ 				Object.defineProperty(fn, name, ObjectFactory(name));
/******/ 			}
/******/ 		}
/******/ 		fn.e = function(chunkId) {
/******/ 			if (hotStatus === "ready") hotSetStatus("prepare");
/******/ 			hotChunksLoading++;
/******/ 			return __webpack_require__.e(chunkId).then(finishChunkLoading, function(err) {
/******/ 				finishChunkLoading();
/******/ 				throw err;
/******/ 			});
/******/
/******/ 			function finishChunkLoading() {
/******/ 				hotChunksLoading--;
/******/ 				if (hotStatus === "prepare") {
/******/ 					if (!hotWaitingFilesMap[chunkId]) {
/******/ 						hotEnsureUpdateChunk(chunkId);
/******/ 					}
/******/ 					if (hotChunksLoading === 0 && hotWaitingFiles === 0) {
/******/ 						hotUpdateDownloaded();
/******/ 					}
/******/ 				}
/******/ 			}
/******/ 		};
/******/ 		return fn;
/******/ 	}
/******/
/******/ 	// eslint-disable-next-line no-unused-vars
/******/ 	function hotCreateModule(moduleId) {
/******/ 		var hot = {
/******/ 			// private stuff
/******/ 			_acceptedDependencies: {},
/******/ 			_declinedDependencies: {},
/******/ 			_selfAccepted: false,
/******/ 			_selfDeclined: false,
/******/ 			_disposeHandlers: [],
/******/ 			_main: hotCurrentChildModule !== moduleId,
/******/
/******/ 			// Module API
/******/ 			active: true,
/******/ 			accept: function(dep, callback) {
/******/ 				if (typeof dep === "undefined") hot._selfAccepted = true;
/******/ 				else if (typeof dep === "function") hot._selfAccepted = dep;
/******/ 				else if (typeof dep === "object")
/******/ 					for (var i = 0; i < dep.length; i++)
/******/ 						hot._acceptedDependencies[dep[i]] = callback || function() {};
/******/ 				else hot._acceptedDependencies[dep] = callback || function() {};
/******/ 			},
/******/ 			decline: function(dep) {
/******/ 				if (typeof dep === "undefined") hot._selfDeclined = true;
/******/ 				else if (typeof dep === "object")
/******/ 					for (var i = 0; i < dep.length; i++)
/******/ 						hot._declinedDependencies[dep[i]] = true;
/******/ 				else hot._declinedDependencies[dep] = true;
/******/ 			},
/******/ 			dispose: function(callback) {
/******/ 				hot._disposeHandlers.push(callback);
/******/ 			},
/******/ 			addDisposeHandler: function(callback) {
/******/ 				hot._disposeHandlers.push(callback);
/******/ 			},
/******/ 			removeDisposeHandler: function(callback) {
/******/ 				var idx = hot._disposeHandlers.indexOf(callback);
/******/ 				if (idx >= 0) hot._disposeHandlers.splice(idx, 1);
/******/ 			},
/******/
/******/ 			// Management API
/******/ 			check: hotCheck,
/******/ 			apply: hotApply,
/******/ 			status: function(l) {
/******/ 				if (!l) return hotStatus;
/******/ 				hotStatusHandlers.push(l);
/******/ 			},
/******/ 			addStatusHandler: function(l) {
/******/ 				hotStatusHandlers.push(l);
/******/ 			},
/******/ 			removeStatusHandler: function(l) {
/******/ 				var idx = hotStatusHandlers.indexOf(l);
/******/ 				if (idx >= 0) hotStatusHandlers.splice(idx, 1);
/******/ 			},
/******/
/******/ 			//inherit from previous dispose call
/******/ 			data: hotCurrentModuleData[moduleId]
/******/ 		};
/******/ 		hotCurrentChildModule = undefined;
/******/ 		return hot;
/******/ 	}
/******/
/******/ 	var hotStatusHandlers = [];
/******/ 	var hotStatus = "idle";
/******/
/******/ 	function hotSetStatus(newStatus) {
/******/ 		hotStatus = newStatus;
/******/ 		for (var i = 0; i < hotStatusHandlers.length; i++)
/******/ 			hotStatusHandlers[i].call(null, newStatus);
/******/ 	}
/******/
/******/ 	// while downloading
/******/ 	var hotWaitingFiles = 0;
/******/ 	var hotChunksLoading = 0;
/******/ 	var hotWaitingFilesMap = {};
/******/ 	var hotRequestedFilesMap = {};
/******/ 	var hotAvailableFilesMap = {};
/******/ 	var hotDeferred;
/******/
/******/ 	// The update info
/******/ 	var hotUpdate, hotUpdateNewHash;
/******/
/******/ 	function toModuleId(id) {
/******/ 		var isNumber = +id + "" === id;
/******/ 		return isNumber ? +id : id;
/******/ 	}
/******/
/******/ 	function hotCheck(apply) {
/******/ 		if (hotStatus !== "idle")
/******/ 			throw new Error("check() is only allowed in idle status");
/******/ 		hotApplyOnUpdate = apply;
/******/ 		hotSetStatus("check");
/******/ 		return hotDownloadManifest(hotRequestTimeout).then(function(update) {
/******/ 			if (!update) {
/******/ 				hotSetStatus("idle");
/******/ 				return null;
/******/ 			}
/******/ 			hotRequestedFilesMap = {};
/******/ 			hotWaitingFilesMap = {};
/******/ 			hotAvailableFilesMap = update.c;
/******/ 			hotUpdateNewHash = update.h;
/******/
/******/ 			hotSetStatus("prepare");
/******/ 			var promise = new Promise(function(resolve, reject) {
/******/ 				hotDeferred = {
/******/ 					resolve: resolve,
/******/ 					reject: reject
/******/ 				};
/******/ 			});
/******/ 			hotUpdate = {};
/******/ 			var chunkId = "main";
/******/ 			{
/******/ 				// eslint-disable-line no-lone-blocks
/******/ 				/*globals chunkId */
/******/ 				hotEnsureUpdateChunk(chunkId);
/******/ 			}
/******/ 			if (
/******/ 				hotStatus === "prepare" &&
/******/ 				hotChunksLoading === 0 &&
/******/ 				hotWaitingFiles === 0
/******/ 			) {
/******/ 				hotUpdateDownloaded();
/******/ 			}
/******/ 			return promise;
/******/ 		});
/******/ 	}
/******/
/******/ 	// eslint-disable-next-line no-unused-vars
/******/ 	function hotAddUpdateChunk(chunkId, moreModules) {
/******/ 		if (!hotAvailableFilesMap[chunkId] || !hotRequestedFilesMap[chunkId])
/******/ 			return;
/******/ 		hotRequestedFilesMap[chunkId] = false;
/******/ 		for (var moduleId in moreModules) {
/******/ 			if (Object.prototype.hasOwnProperty.call(moreModules, moduleId)) {
/******/ 				hotUpdate[moduleId] = moreModules[moduleId];
/******/ 			}
/******/ 		}
/******/ 		if (--hotWaitingFiles === 0 && hotChunksLoading === 0) {
/******/ 			hotUpdateDownloaded();
/******/ 		}
/******/ 	}
/******/
/******/ 	function hotEnsureUpdateChunk(chunkId) {
/******/ 		if (!hotAvailableFilesMap[chunkId]) {
/******/ 			hotWaitingFilesMap[chunkId] = true;
/******/ 		} else {
/******/ 			hotRequestedFilesMap[chunkId] = true;
/******/ 			hotWaitingFiles++;
/******/ 			hotDownloadUpdateChunk(chunkId);
/******/ 		}
/******/ 	}
/******/
/******/ 	function hotUpdateDownloaded() {
/******/ 		hotSetStatus("ready");
/******/ 		var deferred = hotDeferred;
/******/ 		hotDeferred = null;
/******/ 		if (!deferred) return;
/******/ 		if (hotApplyOnUpdate) {
/******/ 			// Wrap deferred object in Promise to mark it as a well-handled Promise to
/******/ 			// avoid triggering uncaught exception warning in Chrome.
/******/ 			// See https://bugs.chromium.org/p/chromium/issues/detail?id=465666
/******/ 			Promise.resolve()
/******/ 				.then(function() {
/******/ 					return hotApply(hotApplyOnUpdate);
/******/ 				})
/******/ 				.then(
/******/ 					function(result) {
/******/ 						deferred.resolve(result);
/******/ 					},
/******/ 					function(err) {
/******/ 						deferred.reject(err);
/******/ 					}
/******/ 				);
/******/ 		} else {
/******/ 			var outdatedModules = [];
/******/ 			for (var id in hotUpdate) {
/******/ 				if (Object.prototype.hasOwnProperty.call(hotUpdate, id)) {
/******/ 					outdatedModules.push(toModuleId(id));
/******/ 				}
/******/ 			}
/******/ 			deferred.resolve(outdatedModules);
/******/ 		}
/******/ 	}
/******/
/******/ 	function hotApply(options) {
/******/ 		if (hotStatus !== "ready")
/******/ 			throw new Error("apply() is only allowed in ready status");
/******/ 		options = options || {};
/******/
/******/ 		var cb;
/******/ 		var i;
/******/ 		var j;
/******/ 		var module;
/******/ 		var moduleId;
/******/
/******/ 		function getAffectedStuff(updateModuleId) {
/******/ 			var outdatedModules = [updateModuleId];
/******/ 			var outdatedDependencies = {};
/******/
/******/ 			var queue = outdatedModules.slice().map(function(id) {
/******/ 				return {
/******/ 					chain: [id],
/******/ 					id: id
/******/ 				};
/******/ 			});
/******/ 			while (queue.length > 0) {
/******/ 				var queueItem = queue.pop();
/******/ 				var moduleId = queueItem.id;
/******/ 				var chain = queueItem.chain;
/******/ 				module = installedModules[moduleId];
/******/ 				if (!module || module.hot._selfAccepted) continue;
/******/ 				if (module.hot._selfDeclined) {
/******/ 					return {
/******/ 						type: "self-declined",
/******/ 						chain: chain,
/******/ 						moduleId: moduleId
/******/ 					};
/******/ 				}
/******/ 				if (module.hot._main) {
/******/ 					return {
/******/ 						type: "unaccepted",
/******/ 						chain: chain,
/******/ 						moduleId: moduleId
/******/ 					};
/******/ 				}
/******/ 				for (var i = 0; i < module.parents.length; i++) {
/******/ 					var parentId = module.parents[i];
/******/ 					var parent = installedModules[parentId];
/******/ 					if (!parent) continue;
/******/ 					if (parent.hot._declinedDependencies[moduleId]) {
/******/ 						return {
/******/ 							type: "declined",
/******/ 							chain: chain.concat([parentId]),
/******/ 							moduleId: moduleId,
/******/ 							parentId: parentId
/******/ 						};
/******/ 					}
/******/ 					if (outdatedModules.indexOf(parentId) !== -1) continue;
/******/ 					if (parent.hot._acceptedDependencies[moduleId]) {
/******/ 						if (!outdatedDependencies[parentId])
/******/ 							outdatedDependencies[parentId] = [];
/******/ 						addAllToSet(outdatedDependencies[parentId], [moduleId]);
/******/ 						continue;
/******/ 					}
/******/ 					delete outdatedDependencies[parentId];
/******/ 					outdatedModules.push(parentId);
/******/ 					queue.push({
/******/ 						chain: chain.concat([parentId]),
/******/ 						id: parentId
/******/ 					});
/******/ 				}
/******/ 			}
/******/
/******/ 			return {
/******/ 				type: "accepted",
/******/ 				moduleId: updateModuleId,
/******/ 				outdatedModules: outdatedModules,
/******/ 				outdatedDependencies: outdatedDependencies
/******/ 			};
/******/ 		}
/******/
/******/ 		function addAllToSet(a, b) {
/******/ 			for (var i = 0; i < b.length; i++) {
/******/ 				var item = b[i];
/******/ 				if (a.indexOf(item) === -1) a.push(item);
/******/ 			}
/******/ 		}
/******/
/******/ 		// at begin all updates modules are outdated
/******/ 		// the "outdated" status can propagate to parents if they don't accept the children
/******/ 		var outdatedDependencies = {};
/******/ 		var outdatedModules = [];
/******/ 		var appliedUpdate = {};
/******/
/******/ 		var warnUnexpectedRequire = function warnUnexpectedRequire() {
/******/ 			console.warn(
/******/ 				"[HMR] unexpected require(" + result.moduleId + ") to disposed module"
/******/ 			);
/******/ 		};
/******/
/******/ 		for (var id in hotUpdate) {
/******/ 			if (Object.prototype.hasOwnProperty.call(hotUpdate, id)) {
/******/ 				moduleId = toModuleId(id);
/******/ 				/** @type {any} */
/******/ 				var result;
/******/ 				if (hotUpdate[id]) {
/******/ 					result = getAffectedStuff(moduleId);
/******/ 				} else {
/******/ 					result = {
/******/ 						type: "disposed",
/******/ 						moduleId: id
/******/ 					};
/******/ 				}
/******/ 				/** @type {Error|false} */
/******/ 				var abortError = false;
/******/ 				var doApply = false;
/******/ 				var doDispose = false;
/******/ 				var chainInfo = "";
/******/ 				if (result.chain) {
/******/ 					chainInfo = "\nUpdate propagation: " + result.chain.join(" -> ");
/******/ 				}
/******/ 				switch (result.type) {
/******/ 					case "self-declined":
/******/ 						if (options.onDeclined) options.onDeclined(result);
/******/ 						if (!options.ignoreDeclined)
/******/ 							abortError = new Error(
/******/ 								"Aborted because of self decline: " +
/******/ 									result.moduleId +
/******/ 									chainInfo
/******/ 							);
/******/ 						break;
/******/ 					case "declined":
/******/ 						if (options.onDeclined) options.onDeclined(result);
/******/ 						if (!options.ignoreDeclined)
/******/ 							abortError = new Error(
/******/ 								"Aborted because of declined dependency: " +
/******/ 									result.moduleId +
/******/ 									" in " +
/******/ 									result.parentId +
/******/ 									chainInfo
/******/ 							);
/******/ 						break;
/******/ 					case "unaccepted":
/******/ 						if (options.onUnaccepted) options.onUnaccepted(result);
/******/ 						if (!options.ignoreUnaccepted)
/******/ 							abortError = new Error(
/******/ 								"Aborted because " + moduleId + " is not accepted" + chainInfo
/******/ 							);
/******/ 						break;
/******/ 					case "accepted":
/******/ 						if (options.onAccepted) options.onAccepted(result);
/******/ 						doApply = true;
/******/ 						break;
/******/ 					case "disposed":
/******/ 						if (options.onDisposed) options.onDisposed(result);
/******/ 						doDispose = true;
/******/ 						break;
/******/ 					default:
/******/ 						throw new Error("Unexception type " + result.type);
/******/ 				}
/******/ 				if (abortError) {
/******/ 					hotSetStatus("abort");
/******/ 					return Promise.reject(abortError);
/******/ 				}
/******/ 				if (doApply) {
/******/ 					appliedUpdate[moduleId] = hotUpdate[moduleId];
/******/ 					addAllToSet(outdatedModules, result.outdatedModules);
/******/ 					for (moduleId in result.outdatedDependencies) {
/******/ 						if (
/******/ 							Object.prototype.hasOwnProperty.call(
/******/ 								result.outdatedDependencies,
/******/ 								moduleId
/******/ 							)
/******/ 						) {
/******/ 							if (!outdatedDependencies[moduleId])
/******/ 								outdatedDependencies[moduleId] = [];
/******/ 							addAllToSet(
/******/ 								outdatedDependencies[moduleId],
/******/ 								result.outdatedDependencies[moduleId]
/******/ 							);
/******/ 						}
/******/ 					}
/******/ 				}
/******/ 				if (doDispose) {
/******/ 					addAllToSet(outdatedModules, [result.moduleId]);
/******/ 					appliedUpdate[moduleId] = warnUnexpectedRequire;
/******/ 				}
/******/ 			}
/******/ 		}
/******/
/******/ 		// Store self accepted outdated modules to require them later by the module system
/******/ 		var outdatedSelfAcceptedModules = [];
/******/ 		for (i = 0; i < outdatedModules.length; i++) {
/******/ 			moduleId = outdatedModules[i];
/******/ 			if (
/******/ 				installedModules[moduleId] &&
/******/ 				installedModules[moduleId].hot._selfAccepted
/******/ 			)
/******/ 				outdatedSelfAcceptedModules.push({
/******/ 					module: moduleId,
/******/ 					errorHandler: installedModules[moduleId].hot._selfAccepted
/******/ 				});
/******/ 		}
/******/
/******/ 		// Now in "dispose" phase
/******/ 		hotSetStatus("dispose");
/******/ 		Object.keys(hotAvailableFilesMap).forEach(function(chunkId) {
/******/ 			if (hotAvailableFilesMap[chunkId] === false) {
/******/ 				hotDisposeChunk(chunkId);
/******/ 			}
/******/ 		});
/******/
/******/ 		var idx;
/******/ 		var queue = outdatedModules.slice();
/******/ 		while (queue.length > 0) {
/******/ 			moduleId = queue.pop();
/******/ 			module = installedModules[moduleId];
/******/ 			if (!module) continue;
/******/
/******/ 			var data = {};
/******/
/******/ 			// Call dispose handlers
/******/ 			var disposeHandlers = module.hot._disposeHandlers;
/******/ 			for (j = 0; j < disposeHandlers.length; j++) {
/******/ 				cb = disposeHandlers[j];
/******/ 				cb(data);
/******/ 			}
/******/ 			hotCurrentModuleData[moduleId] = data;
/******/
/******/ 			// disable module (this disables requires from this module)
/******/ 			module.hot.active = false;
/******/
/******/ 			// remove module from cache
/******/ 			delete installedModules[moduleId];
/******/
/******/ 			// when disposing there is no need to call dispose handler
/******/ 			delete outdatedDependencies[moduleId];
/******/
/******/ 			// remove "parents" references from all children
/******/ 			for (j = 0; j < module.children.length; j++) {
/******/ 				var child = installedModules[module.children[j]];
/******/ 				if (!child) continue;
/******/ 				idx = child.parents.indexOf(moduleId);
/******/ 				if (idx >= 0) {
/******/ 					child.parents.splice(idx, 1);
/******/ 				}
/******/ 			}
/******/ 		}
/******/
/******/ 		// remove outdated dependency from module children
/******/ 		var dependency;
/******/ 		var moduleOutdatedDependencies;
/******/ 		for (moduleId in outdatedDependencies) {
/******/ 			if (
/******/ 				Object.prototype.hasOwnProperty.call(outdatedDependencies, moduleId)
/******/ 			) {
/******/ 				module = installedModules[moduleId];
/******/ 				if (module) {
/******/ 					moduleOutdatedDependencies = outdatedDependencies[moduleId];
/******/ 					for (j = 0; j < moduleOutdatedDependencies.length; j++) {
/******/ 						dependency = moduleOutdatedDependencies[j];
/******/ 						idx = module.children.indexOf(dependency);
/******/ 						if (idx >= 0) module.children.splice(idx, 1);
/******/ 					}
/******/ 				}
/******/ 			}
/******/ 		}
/******/
/******/ 		// Not in "apply" phase
/******/ 		hotSetStatus("apply");
/******/
/******/ 		hotCurrentHash = hotUpdateNewHash;
/******/
/******/ 		// insert new code
/******/ 		for (moduleId in appliedUpdate) {
/******/ 			if (Object.prototype.hasOwnProperty.call(appliedUpdate, moduleId)) {
/******/ 				modules[moduleId] = appliedUpdate[moduleId];
/******/ 			}
/******/ 		}
/******/
/******/ 		// call accept handlers
/******/ 		var error = null;
/******/ 		for (moduleId in outdatedDependencies) {
/******/ 			if (
/******/ 				Object.prototype.hasOwnProperty.call(outdatedDependencies, moduleId)
/******/ 			) {
/******/ 				module = installedModules[moduleId];
/******/ 				if (module) {
/******/ 					moduleOutdatedDependencies = outdatedDependencies[moduleId];
/******/ 					var callbacks = [];
/******/ 					for (i = 0; i < moduleOutdatedDependencies.length; i++) {
/******/ 						dependency = moduleOutdatedDependencies[i];
/******/ 						cb = module.hot._acceptedDependencies[dependency];
/******/ 						if (cb) {
/******/ 							if (callbacks.indexOf(cb) !== -1) continue;
/******/ 							callbacks.push(cb);
/******/ 						}
/******/ 					}
/******/ 					for (i = 0; i < callbacks.length; i++) {
/******/ 						cb = callbacks[i];
/******/ 						try {
/******/ 							cb(moduleOutdatedDependencies);
/******/ 						} catch (err) {
/******/ 							if (options.onErrored) {
/******/ 								options.onErrored({
/******/ 									type: "accept-errored",
/******/ 									moduleId: moduleId,
/******/ 									dependencyId: moduleOutdatedDependencies[i],
/******/ 									error: err
/******/ 								});
/******/ 							}
/******/ 							if (!options.ignoreErrored) {
/******/ 								if (!error) error = err;
/******/ 							}
/******/ 						}
/******/ 					}
/******/ 				}
/******/ 			}
/******/ 		}
/******/
/******/ 		// Load self accepted modules
/******/ 		for (i = 0; i < outdatedSelfAcceptedModules.length; i++) {
/******/ 			var item = outdatedSelfAcceptedModules[i];
/******/ 			moduleId = item.module;
/******/ 			hotCurrentParents = [moduleId];
/******/ 			try {
/******/ 				__webpack_require__(moduleId);
/******/ 			} catch (err) {
/******/ 				if (typeof item.errorHandler === "function") {
/******/ 					try {
/******/ 						item.errorHandler(err);
/******/ 					} catch (err2) {
/******/ 						if (options.onErrored) {
/******/ 							options.onErrored({
/******/ 								type: "self-accept-error-handler-errored",
/******/ 								moduleId: moduleId,
/******/ 								error: err2,
/******/ 								originalError: err
/******/ 							});
/******/ 						}
/******/ 						if (!options.ignoreErrored) {
/******/ 							if (!error) error = err2;
/******/ 						}
/******/ 						if (!error) error = err;
/******/ 					}
/******/ 				} else {
/******/ 					if (options.onErrored) {
/******/ 						options.onErrored({
/******/ 							type: "self-accept-errored",
/******/ 							moduleId: moduleId,
/******/ 							error: err
/******/ 						});
/******/ 					}
/******/ 					if (!options.ignoreErrored) {
/******/ 						if (!error) error = err;
/******/ 					}
/******/ 				}
/******/ 			}
/******/ 		}
/******/
/******/ 		// handle errors in accept handlers and self accepted module load
/******/ 		if (error) {
/******/ 			hotSetStatus("fail");
/******/ 			return Promise.reject(error);
/******/ 		}
/******/
/******/ 		hotSetStatus("idle");
/******/ 		return new Promise(function(resolve) {
/******/ 			resolve(outdatedModules);
/******/ 		});
/******/ 	}
/******/
/******/ 	// The module cache
/******/ 	var installedModules = {};
/******/
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/
/******/ 		// Check if module is in cache
/******/ 		if(installedModules[moduleId]) {
/******/ 			return installedModules[moduleId].exports;
/******/ 		}
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = installedModules[moduleId] = {
/******/ 			i: moduleId,
/******/ 			l: false,
/******/ 			exports: {},
/******/ 			hot: hotCreateModule(moduleId),
/******/ 			parents: (hotCurrentParentsTemp = hotCurrentParents, hotCurrentParents = [], hotCurrentParentsTemp),
/******/ 			children: []
/******/ 		};
/******/
/******/ 		// Execute the module function
/******/ 		modules[moduleId].call(module.exports, module, module.exports, hotCreateRequire(moduleId));
/******/
/******/ 		// Flag the module as loaded
/******/ 		module.l = true;
/******/
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/
/******/
/******/ 	// expose the modules object (__webpack_modules__)
/******/ 	__webpack_require__.m = modules;
/******/
/******/ 	// expose the module cache
/******/ 	__webpack_require__.c = installedModules;
/******/
/******/ 	// define getter function for harmony exports
/******/ 	__webpack_require__.d = function(exports, name, getter) {
/******/ 		if(!__webpack_require__.o(exports, name)) {
/******/ 			Object.defineProperty(exports, name, {
/******/ 				configurable: false,
/******/ 				enumerable: true,
/******/ 				get: getter
/******/ 			});
/******/ 		}
/******/ 	};
/******/
/******/ 	// define __esModule on exports
/******/ 	__webpack_require__.r = function(exports) {
/******/ 		Object.defineProperty(exports, '__esModule', { value: true });
/******/ 	};
/******/
/******/ 	// getDefaultExport function for compatibility with non-harmony modules
/******/ 	__webpack_require__.n = function(module) {
/******/ 		var getter = module && module.__esModule ?
/******/ 			function getDefault() { return module['default']; } :
/******/ 			function getModuleExports() { return module; };
/******/ 		__webpack_require__.d(getter, 'a', getter);
/******/ 		return getter;
/******/ 	};
/******/
/******/ 	// Object.prototype.hasOwnProperty.call
/******/ 	__webpack_require__.o = function(object, property) { return Object.prototype.hasOwnProperty.call(object, property); };
/******/
/******/ 	// __webpack_public_path__
/******/ 	__webpack_require__.p = "";
/******/
/******/ 	// __webpack_hash__
/******/ 	__webpack_require__.h = function() { return hotCurrentHash; };
/******/
/******/
/******/ 	// Load entry module and return exports
/******/ 	return hotCreateRequire(0)(__webpack_require__.s = 0);
/******/ })
/************************************************************************/
/******/ ({

/***/ "./node_modules/electron-webpack/out/electron-main-hmr/main-hmr.js":
/*!*************************************************************************!*\
  !*** ./node_modules/electron-webpack/out/electron-main-hmr/main-hmr.js ***!
  \*************************************************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
eval("\n\n__webpack_require__(/*! source-map-support/source-map-support.js */ \"source-map-support/source-map-support.js\").install();\n\nconst socketPath = process.env.ELECTRON_HMR_SOCKET_PATH;\n\nif (socketPath == null) {\n  throw new Error(`[HMR] Env ELECTRON_HMR_SOCKET_PATH is not set`);\n} // module, but not relative path must be used (because this file is used as entry)\n\n\nconst HmrClient = __webpack_require__(/*! electron-webpack/out/electron-main-hmr/HmrClient */ \"electron-webpack/out/electron-main-hmr/HmrClient\").HmrClient; // tslint:disable:no-unused-expression\n\n\nnew HmrClient(socketPath, module.hot, () => {\n  return __webpack_require__.h();\n}); \n//# sourceMappingURL=main-hmr.js.map//# sourceURL=[module]\n//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJzb3VyY2VzIjpbIndlYnBhY2s6Ly8vLi9ub2RlX21vZHVsZXMvZWxlY3Ryb24td2VicGFjay9vdXQvZWxlY3Ryb24tbWFpbi1obXIvbWFpbi1obXIuanM/MWJkYyJdLCJuYW1lcyI6W10sIm1hcHBpbmdzIjoiQUFBQTs7QUFFQTs7QUFFQTs7QUFFQTtBQUNBO0FBQ0EsQ0FBQzs7O0FBR0QsNEpBQXdGOzs7QUFHeEY7QUFDQTtBQUNBLENBQUMsRTtBQUNEIiwiZmlsZSI6Ii4vbm9kZV9tb2R1bGVzL2VsZWN0cm9uLXdlYnBhY2svb3V0L2VsZWN0cm9uLW1haW4taG1yL21haW4taG1yLmpzLmpzIiwic291cmNlc0NvbnRlbnQiOlsiXCJ1c2Ugc3RyaWN0XCI7XG5cbnJlcXVpcmUoXCJzb3VyY2UtbWFwLXN1cHBvcnQvc291cmNlLW1hcC1zdXBwb3J0LmpzXCIpLmluc3RhbGwoKTtcblxuY29uc3Qgc29ja2V0UGF0aCA9IHByb2Nlc3MuZW52LkVMRUNUUk9OX0hNUl9TT0NLRVRfUEFUSDtcblxuaWYgKHNvY2tldFBhdGggPT0gbnVsbCkge1xuICB0aHJvdyBuZXcgRXJyb3IoYFtITVJdIEVudiBFTEVDVFJPTl9ITVJfU09DS0VUX1BBVEggaXMgbm90IHNldGApO1xufSAvLyBtb2R1bGUsIGJ1dCBub3QgcmVsYXRpdmUgcGF0aCBtdXN0IGJlIHVzZWQgKGJlY2F1c2UgdGhpcyBmaWxlIGlzIHVzZWQgYXMgZW50cnkpXG5cblxuY29uc3QgSG1yQ2xpZW50ID0gcmVxdWlyZShcImVsZWN0cm9uLXdlYnBhY2svb3V0L2VsZWN0cm9uLW1haW4taG1yL0htckNsaWVudFwiKS5IbXJDbGllbnQ7IC8vIHRzbGludDpkaXNhYmxlOm5vLXVudXNlZC1leHByZXNzaW9uXG5cblxubmV3IEhtckNsaWVudChzb2NrZXRQYXRoLCBtb2R1bGUuaG90LCAoKSA9PiB7XG4gIHJldHVybiBfX3dlYnBhY2tfaGFzaF9fO1xufSk7IFxuLy8jIHNvdXJjZU1hcHBpbmdVUkw9bWFpbi1obXIuanMubWFwIl0sInNvdXJjZVJvb3QiOiIifQ==\n//# sourceURL=webpack-internal:///./node_modules/electron-webpack/out/electron-main-hmr/main-hmr.js\n");

/***/ }),

/***/ "./src/common/window.ts":
/*!******************************!*\
  !*** ./src/common/window.ts ***!
  \******************************/
/*! exports provided: WindowName, getIndexLocation, createRendererWindow */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, \"WindowName\", function() { return WindowName; });\n/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, \"getIndexLocation\", function() { return getIndexLocation; });\n/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, \"createRendererWindow\", function() { return createRendererWindow; });\n/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! electron */ \"electron\");\n/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(electron__WEBPACK_IMPORTED_MODULE_0__);\n/* harmony import */ var _main_errors__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ../main/errors */ \"./src/main/errors.ts\");\n\n\nvar WindowName;\n(function (WindowName) {\n    WindowName[\"APP\"] = \"app\";\n    WindowName[\"BACKGROUND\"] = \"background\";\n})(WindowName || (WindowName = {}));\nfunction getIndexLocation() {\n    return  true\n        ? `http://localhost:${process.env.ELECTRON_WEBPACK_WDS_PORT}/`\n        : undefined;\n}\nfunction createRendererWindow({ window: windowOptions, name, show }) {\n    const window = new electron__WEBPACK_IMPORTED_MODULE_0__[\"BrowserWindow\"](Object.assign({ show }, windowOptions));\n    const args = {\n        name,\n    };\n    const url = getIndexLocation();\n    window.loadURL(`${url}#${encodeURIComponent(JSON.stringify(args))}`);\n    window.webContents.on('crashed', (event, killed) => {\n        if (!killed) {\n            Object(_main_errors__WEBPACK_IMPORTED_MODULE_1__[\"handleError\"])(event);\n        }\n    });\n    if (show) {\n        window.webContents.on('did-finish-load', () => {\n            window.show();\n            window.focus();\n        });\n    }\n    window.on('unresponsive', () => {\n        Object(_main_errors__WEBPACK_IMPORTED_MODULE_1__[\"handleError\"])(new Error('An app window became unresponsive.'));\n    });\n    return window;\n}\n//# sourceURL=[module]\n//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJzb3VyY2VzIjpbIndlYnBhY2s6Ly8vLi9zcmMvY29tbW9uL3dpbmRvdy50cz9hNzg5Il0sIm5hbWVzIjpbXSwibWFwcGluZ3MiOiI7Ozs7Ozs7QUFBMEU7QUFDN0I7QUFFN0MsSUFBWSxVQUdYO0FBSEQsV0FBWSxVQUFVO0lBQ3BCLHlCQUFXO0lBQ1gsdUNBQXlCO0FBQzNCLENBQUMsRUFIVyxVQUFVLEtBQVYsVUFBVSxRQUdyQjtBQUVLO0lBQ0osT0FBTyxLQUFzQztRQUMzQyxDQUFDLENBQUMsb0JBQW9CLE9BQU8sQ0FBQyxHQUFHLENBQUMseUJBQXlCLEdBQUc7UUFDOUQsQ0FBQyxDQUFDLFNBQTBCLENBQUM7QUFDakMsQ0FBQztBQVFLLDhCQUErQixFQUFFLE1BQU0sRUFBRSxhQUFhLEVBQUUsSUFBSSxFQUFFLElBQUksRUFBeUI7SUFDL0YsTUFBTSxNQUFNLEdBQUcsSUFBSSxzREFBYSxpQkFDOUIsSUFBSSxJQUNELGFBQWEsRUFDaEIsQ0FBQztJQUVILE1BQU0sSUFBSSxHQUFHO1FBQ1gsSUFBSTtLQUNMLENBQUM7SUFFRixNQUFNLEdBQUcsR0FBRyxnQkFBZ0IsRUFBRSxDQUFDO0lBQy9CLE1BQU0sQ0FBQyxPQUFPLENBQUMsR0FBRyxHQUFHLElBQUksa0JBQWtCLENBQUMsSUFBSSxDQUFDLFNBQVMsQ0FBQyxJQUFJLENBQUMsQ0FBQyxFQUFFLENBQUMsQ0FBQztJQUNyRSxNQUFNLENBQUMsV0FBVyxDQUFDLEVBQUUsQ0FBQyxTQUFTLEVBQUUsQ0FBQyxLQUFLLEVBQUUsTUFBTSxFQUFFLEVBQUU7UUFDakQsSUFBSSxDQUFDLE1BQU0sRUFBRTtZQUNYLGdFQUFXLENBQUMsS0FBSyxDQUFDLENBQUM7U0FDcEI7SUFDSCxDQUFDLENBQUMsQ0FBQztJQUNILElBQUksSUFBSSxFQUFFO1FBQ1IsTUFBTSxDQUFDLFdBQVcsQ0FBQyxFQUFFLENBQUMsaUJBQWlCLEVBQUUsR0FBRyxFQUFFO1lBQzVDLE1BQU0sQ0FBQyxJQUFJLEVBQUUsQ0FBQztZQUNkLE1BQU0sQ0FBQyxLQUFLLEVBQUUsQ0FBQztRQUNqQixDQUFDLENBQUMsQ0FBQztLQUNKO0lBRUQsTUFBTSxDQUFDLEVBQUUsQ0FBQyxjQUFjLEVBQUUsR0FBRyxFQUFFO1FBQzdCLGdFQUFXLENBQUMsSUFBSSxLQUFLLENBQUMsb0NBQW9DLENBQUMsQ0FBQyxDQUFDO0lBQy9ELENBQUMsQ0FBQyxDQUFDO0lBRUgsT0FBTyxNQUFNLENBQUM7QUFDaEIsQ0FBQyIsImZpbGUiOiIuL3NyYy9jb21tb24vd2luZG93LnRzLmpzIiwic291cmNlc0NvbnRlbnQiOlsiaW1wb3J0IHsgQnJvd3NlcldpbmRvdywgQnJvd3NlcldpbmRvd0NvbnN0cnVjdG9yT3B0aW9ucyB9IGZyb20gJ2VsZWN0cm9uJztcbmltcG9ydCB7IGhhbmRsZUVycm9yIH0gZnJvbSAnLi4vbWFpbi9lcnJvcnMnO1xuXG5leHBvcnQgZW51bSBXaW5kb3dOYW1lIHtcbiAgQVBQID0gJ2FwcCcsXG4gIEJBQ0tHUk9VTkQgPSAnYmFja2dyb3VuZCcsXG59XG5cbmV4cG9ydCBmdW5jdGlvbiBnZXRJbmRleExvY2F0aW9uKCkge1xuICByZXR1cm4gcHJvY2Vzcy5lbnYuTk9ERV9FTlYgPT09ICdkZXZlbG9wbWVudCdcbiAgICA/IGBodHRwOi8vbG9jYWxob3N0OiR7cHJvY2Vzcy5lbnYuRUxFQ1RST05fV0VCUEFDS19XRFNfUE9SVH0vYFxuICAgIDogYCR7X19kaXJuYW1lfVxcXFxpbmRleC5odG1sYDtcbn1cblxudHlwZSBSZW5kZXJlcldpbmRvd09wdGlvbnMgPSB7XG4gIHdpbmRvdz86IEJyb3dzZXJXaW5kb3dDb25zdHJ1Y3Rvck9wdGlvbnMsXG4gIG5hbWU6IFdpbmRvd05hbWU7XG4gIHNob3c6IGJvb2xlYW47XG59O1xuXG5leHBvcnQgZnVuY3Rpb24gY3JlYXRlUmVuZGVyZXJXaW5kb3coeyB3aW5kb3c6IHdpbmRvd09wdGlvbnMsIG5hbWUsIHNob3cgfTogUmVuZGVyZXJXaW5kb3dPcHRpb25zKSB7XG4gIGNvbnN0IHdpbmRvdyA9IG5ldyBCcm93c2VyV2luZG93KHtcbiAgICBzaG93LFxuICAgIC4uLndpbmRvd09wdGlvbnMsXG4gIH0pO1xuXG4gIGNvbnN0IGFyZ3MgPSB7XG4gICAgbmFtZSxcbiAgfTtcblxuICBjb25zdCB1cmwgPSBnZXRJbmRleExvY2F0aW9uKCk7XG4gIHdpbmRvdy5sb2FkVVJMKGAke3VybH0jJHtlbmNvZGVVUklDb21wb25lbnQoSlNPTi5zdHJpbmdpZnkoYXJncykpfWApO1xuICB3aW5kb3cud2ViQ29udGVudHMub24oJ2NyYXNoZWQnLCAoZXZlbnQsIGtpbGxlZCkgPT4ge1xuICAgIGlmICgha2lsbGVkKSB7XG4gICAgICBoYW5kbGVFcnJvcihldmVudCk7XG4gICAgfVxuICB9KTtcbiAgaWYgKHNob3cpIHtcbiAgICB3aW5kb3cud2ViQ29udGVudHMub24oJ2RpZC1maW5pc2gtbG9hZCcsICgpID0+IHtcbiAgICAgIHdpbmRvdy5zaG93KCk7XG4gICAgICB3aW5kb3cuZm9jdXMoKTtcbiAgICB9KTtcbiAgfVxuXG4gIHdpbmRvdy5vbigndW5yZXNwb25zaXZlJywgKCkgPT4ge1xuICAgIGhhbmRsZUVycm9yKG5ldyBFcnJvcignQW4gYXBwIHdpbmRvdyBiZWNhbWUgdW5yZXNwb25zaXZlLicpKTtcbiAgfSk7XG5cbiAgcmV0dXJuIHdpbmRvdztcbn1cbiJdLCJzb3VyY2VSb290IjoiIn0=\n//# sourceURL=webpack-internal:///./src/common/window.ts\n");

/***/ }),

/***/ "./src/main/errors.ts":
/*!****************************!*\
  !*** ./src/main/errors.ts ***!
  \****************************/
/*! exports provided: handleError */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, \"handleError\", function() { return handleError; });\n/* harmony import */ var raven_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! raven-js */ \"raven-js\");\n/* harmony import */ var raven_js__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(raven_js__WEBPACK_IMPORTED_MODULE_0__);\n\nraven_js__WEBPACK_IMPORTED_MODULE_0___default.a\n    .install();\nconst handleError = error => {\n    if (false) {}\n    else {\n        console.error(error);\n    }\n};\n//# sourceURL=[module]\n//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJzb3VyY2VzIjpbIndlYnBhY2s6Ly8vLi9zcmMvbWFpbi9lcnJvcnMudHM/Y2NjOCJdLCJuYW1lcyI6W10sIm1hcHBpbmdzIjoiOzs7O0FBQTZCO0FBRTdCLCtDQUFLO0tBQ0YsT0FBTyxFQUFFLENBQUM7QUFFTixNQUFNLFdBQVcsR0FBRyxLQUFLLENBQUMsRUFBRTtJQUNqQyxJQUFJLEtBQXFDLEVBQUUsRUFFMUM7U0FBTTtRQUNMLE9BQU8sQ0FBQyxLQUFLLENBQUMsS0FBSyxDQUFDLENBQUM7S0FDdEI7QUFDSCxDQUFDLENBQUMiLCJmaWxlIjoiLi9zcmMvbWFpbi9lcnJvcnMudHMuanMiLCJzb3VyY2VzQ29udGVudCI6WyJpbXBvcnQgUmF2ZW4gZnJvbSAncmF2ZW4tanMnO1xuXG5SYXZlblxuICAuaW5zdGFsbCgpO1xuXG5leHBvcnQgY29uc3QgaGFuZGxlRXJyb3IgPSBlcnJvciA9PiB7XG4gIGlmIChwcm9jZXNzLmVudi5OT0RFX0VOViA9PT0gJ3Byb2R1Y3Rpb24nKSB7XG4gICAgUmF2ZW4uY2FwdHVyZUV4Y2VwdGlvbihlcnJvcik7XG4gIH0gZWxzZSB7XG4gICAgY29uc29sZS5lcnJvcihlcnJvcik7XG4gIH1cbn07XG4iXSwic291cmNlUm9vdCI6IiJ9\n//# sourceURL=webpack-internal:///./src/main/errors.ts\n");

/***/ }),

/***/ "./src/main/index.ts":
/*!***************************!*\
  !*** ./src/main/index.ts ***!
  \***************************/
/*! no exports provided */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* WEBPACK VAR INJECTION */(function(__dirname) {/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! electron */ \"electron\");\n/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(electron__WEBPACK_IMPORTED_MODULE_0__);\n/* harmony import */ var _common_window__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ../common/window */ \"./src/common/window.ts\");\n/* harmony import */ var _errors__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! ./errors */ \"./src/main/errors.ts\");\n/* harmony import */ var _menu__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! ./menu */ \"./src/main/menu.ts\");\n// eslint-disable global-require\n\n\n\n\nlet mainWindow = null;\nlet backgroundWindow = null;\nconst installExtensions = () => {\n    if (true) {\n        const { default: installExtension, REACT_DEVELOPER_TOOLS, REDUX_DEVTOOLS } = __webpack_require__(/*! electron-devtools-installer */ \"electron-devtools-installer\");\n        const extensions = [\n            REACT_DEVELOPER_TOOLS,\n            REDUX_DEVTOOLS,\n        ];\n        const forceDownload = !!process.env.UPGRADE_EXTENSIONS;\n        return Promise.all(extensions.map(extension => installExtension(extension.id, forceDownload)))\n            .then(() => void 0);\n    }\n    return Promise.resolve();\n};\nprocess.on('uncaughtException', error => {\n    Object(_errors__WEBPACK_IMPORTED_MODULE_2__[\"handleError\"])(error);\n});\nelectron__WEBPACK_IMPORTED_MODULE_0__[\"app\"].on('ready', () => installExtensions().then(() => {\n    backgroundWindow = Object(_common_window__WEBPACK_IMPORTED_MODULE_1__[\"createRendererWindow\"])({\n        name: _common_window__WEBPACK_IMPORTED_MODULE_1__[\"WindowName\"].BACKGROUND,\n        show: false,\n    });\n    mainWindow = Object(_common_window__WEBPACK_IMPORTED_MODULE_1__[\"createRendererWindow\"])({\n        window: {\n            width: 1024,\n            height: 728,\n        },\n        show: true,\n        name: _common_window__WEBPACK_IMPORTED_MODULE_1__[\"WindowName\"].APP,\n    });\n    Object(_menu__WEBPACK_IMPORTED_MODULE_3__[\"setMenu\"])(mainWindow);\n    mainWindow.on('closed', () => {\n        mainWindow = null;\n        backgroundWindow = null;\n    });\n    if (false) {}\n    else if (true) {\n        mainWindow.openDevTools();\n        mainWindow.webContents.on('context-menu', (_e, props) => {\n            const { x, y } = props;\n            electron__WEBPACK_IMPORTED_MODULE_0__[\"Menu\"].buildFromTemplate([\n                {\n                    label: 'Inspect element',\n                    click: () => mainWindow.webContents.inspectElement(x, y),\n                },\n            ]).popup(mainWindow);\n        });\n        __webpack_require__(/*! electron-debug */ \"electron-debug\")();\n        const path = __webpack_require__(/*! path */ \"path\");\n        const p = path.join(__dirname, './node_modules');\n        __webpack_require__(/*! module */ \"module\").globalPaths.push(p);\n    }\n}));\nelectron__WEBPACK_IMPORTED_MODULE_0__[\"app\"].on('window-all-closed', () => {\n    if (process.platform !== 'darwin') {\n        electron__WEBPACK_IMPORTED_MODULE_0__[\"app\"].quit();\n    }\n});\nelectron__WEBPACK_IMPORTED_MODULE_0__[\"ipcMain\"].on('renderer', (event, payload) => {\n    console.log(event);\n    console.log(payload);\n    mainWindow.webContents.send('main', payload);\n});\nelectron__WEBPACK_IMPORTED_MODULE_0__[\"ipcMain\"].on('background', (event, payload) => {\n    console.log(event);\n    console.log(payload);\n    backgroundWindow.webContents.send('main', payload);\n});\n\n/* WEBPACK VAR INJECTION */}.call(this, \"src/main\"))//# sourceURL=[module]\n//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJzb3VyY2VzIjpbIndlYnBhY2s6Ly8vLi9zcmMvbWFpbi9pbmRleC50cz8wNWI2Il0sIm5hbWVzIjpbXSwibWFwcGluZ3MiOiI7Ozs7O0FBQUE7QUFBQSxnQ0FBZ0M7QUFDYztBQUNzQjtBQUM3QjtBQUNOO0FBRWpDLElBQUksVUFBVSxHQUFHLElBQUksQ0FBQztBQUN0QixJQUFJLGdCQUFnQixHQUFHLElBQUksQ0FBQztBQUU1QixNQUFNLGlCQUFpQixHQUFHLEdBQWtCLEVBQUU7SUFDNUMsSUFBSSxJQUFzQyxFQUFFO1FBQzFDLE1BQU0sRUFBRSxPQUFPLEVBQUUsZ0JBQWdCLEVBQUUscUJBQXFCLEVBQUUsY0FBYyxFQUFFLEdBQUcsbUJBQU8sQ0FBQyxnRUFBNkIsQ0FBQyxDQUFDO1FBRXBILE1BQU0sVUFBVSxHQUFHO1lBQ2pCLHFCQUFxQjtZQUNyQixjQUFjO1NBQ2YsQ0FBQztRQUVGLE1BQU0sYUFBYSxHQUFHLENBQUMsQ0FBQyxPQUFPLENBQUMsR0FBRyxDQUFDLGtCQUFrQixDQUFDO1FBQ3ZELE9BQU8sT0FBTyxDQUFDLEdBQUcsQ0FBQyxVQUFVLENBQUMsR0FBRyxDQUFDLFNBQVMsQ0FBQyxFQUFFLENBQUMsZ0JBQWdCLENBQUMsU0FBUyxDQUFDLEVBQUUsRUFBRSxhQUFhLENBQUMsQ0FBQyxDQUFDO2FBQzNGLElBQUksQ0FBQyxHQUFHLEVBQUUsQ0FBQyxLQUFLLENBQUMsQ0FBQyxDQUFDO0tBQ3ZCO0lBQ0QsT0FBTyxPQUFPLENBQUMsT0FBTyxFQUFFLENBQUM7QUFDM0IsQ0FBQyxDQUFDO0FBRUYsT0FBTyxDQUFDLEVBQUUsQ0FBQyxtQkFBbUIsRUFBRSxLQUFLLENBQUMsRUFBRTtJQUN0QywyREFBVyxDQUFDLEtBQUssQ0FBQyxDQUFDO0FBQ3JCLENBQUMsQ0FBQyxDQUFDO0FBRUgsNENBQUcsQ0FBQyxFQUFFLENBQUMsT0FBTyxFQUFFLEdBQUcsRUFBRSxDQUFDLGlCQUFpQixFQUFFLENBQUMsSUFBSSxDQUFDLEdBQUcsRUFBRTtJQUNsRCxnQkFBZ0IsR0FBRywyRUFBb0IsQ0FBQztRQUN0QyxJQUFJLEVBQUUseURBQVUsQ0FBQyxVQUFVO1FBQzNCLElBQUksRUFBRSxLQUFLO0tBQ1osQ0FBQyxDQUFDO0lBQ0gsVUFBVSxHQUFHLDJFQUFvQixDQUFDO1FBQ2hDLE1BQU0sRUFBRTtZQUNOLEtBQUssRUFBRSxJQUFJO1lBQ1gsTUFBTSxFQUFFLEdBQUc7U0FDWjtRQUNELElBQUksRUFBRSxJQUFJO1FBQ1YsSUFBSSxFQUFFLHlEQUFVLENBQUMsR0FBRztLQUNyQixDQUFDLENBQUM7SUFDSCxxREFBTyxDQUFDLFVBQVUsQ0FBQyxDQUFDO0lBQ3BCLFVBQVUsQ0FBQyxFQUFFLENBQUMsUUFBUSxFQUFFLEdBQUcsRUFBRTtRQUMzQixVQUFVLEdBQUcsSUFBSSxDQUFDO1FBQ2xCLGdCQUFnQixHQUFHLElBQUksQ0FBQztJQUMxQixDQUFDLENBQUMsQ0FBQztJQUNILElBQUksS0FBcUMsRUFBRSxFQUcxQztTQUFNLElBQUksSUFBc0MsRUFBRTtRQUNqRCxVQUFVLENBQUMsWUFBWSxFQUFFLENBQUM7UUFDMUIsVUFBVSxDQUFDLFdBQVcsQ0FBQyxFQUFFLENBQUMsY0FBYyxFQUFFLENBQUMsRUFBRSxFQUFFLEtBQUssRUFBRSxFQUFFO1lBQ3RELE1BQU0sRUFBRSxDQUFDLEVBQUUsQ0FBQyxFQUFFLEdBQUcsS0FBSyxDQUFDO1lBQ3ZCLDZDQUFJLENBQUMsaUJBQWlCLENBQUM7Z0JBQ3JCO29CQUNFLEtBQUssRUFBRSxpQkFBaUI7b0JBQ3hCLEtBQUssRUFBRSxHQUFHLEVBQUUsQ0FBQyxVQUFVLENBQUMsV0FBVyxDQUFDLGNBQWMsQ0FBQyxDQUFDLEVBQUUsQ0FBQyxDQUFDO2lCQUN6RDthQUNGLENBQUMsQ0FBQyxLQUFLLENBQUMsVUFBVSxDQUFDLENBQUM7UUFDdkIsQ0FBQyxDQUFDLENBQUM7UUFDSCxtQkFBTyxDQUFDLHNDQUFnQixDQUFDLEVBQUUsQ0FBQztRQUM1QixNQUFNLElBQUksR0FBRyxtQkFBTyxDQUFDLGtCQUFNLENBQUMsQ0FBQztRQUM3QixNQUFNLENBQUMsR0FBRyxJQUFJLENBQUMsSUFBSSxDQUFDLFNBQVMsRUFBRSxnQkFBZ0IsQ0FBQyxDQUFDO1FBQ2pELG1CQUFPLENBQUMsc0JBQVEsQ0FBQyxDQUFDLFdBQVcsQ0FBQyxJQUFJLENBQUMsQ0FBQyxDQUFDLENBQUM7S0FDdkM7QUFDSCxDQUFDLENBQUMsQ0FBQyxDQUFDO0FBRUosNENBQUcsQ0FBQyxFQUFFLENBQUMsbUJBQW1CLEVBQUUsR0FBRyxFQUFFO0lBQy9CLElBQUksT0FBTyxDQUFDLFFBQVEsS0FBSyxRQUFRLEVBQUU7UUFDakMsNENBQUcsQ0FBQyxJQUFJLEVBQUUsQ0FBQztLQUNaO0FBQ0gsQ0FBQyxDQUFDLENBQUM7QUFFSCxnREFBTyxDQUFDLEVBQUUsQ0FBQyxVQUFVLEVBQUUsQ0FBQyxLQUFLLEVBQUUsT0FBTyxFQUFFLEVBQUU7SUFDeEMsT0FBTyxDQUFDLEdBQUcsQ0FBQyxLQUFLLENBQUMsQ0FBQztJQUNuQixPQUFPLENBQUMsR0FBRyxDQUFDLE9BQU8sQ0FBQyxDQUFDO0lBQ3JCLFVBQVUsQ0FBQyxXQUFXLENBQUMsSUFBSSxDQUFDLE1BQU0sRUFBRSxPQUFPLENBQUMsQ0FBQztBQUMvQyxDQUFDLENBQUMsQ0FBQztBQUVILGdEQUFPLENBQUMsRUFBRSxDQUFDLFlBQVksRUFBRSxDQUFDLEtBQUssRUFBRSxPQUFPLEVBQUUsRUFBRTtJQUMxQyxPQUFPLENBQUMsR0FBRyxDQUFDLEtBQUssQ0FBQyxDQUFDO0lBQ25CLE9BQU8sQ0FBQyxHQUFHLENBQUMsT0FBTyxDQUFDLENBQUM7SUFDckIsZ0JBQWdCLENBQUMsV0FBVyxDQUFDLElBQUksQ0FBQyxNQUFNLEVBQUUsT0FBTyxDQUFDLENBQUM7QUFDckQsQ0FBQyxDQUFDLENBQUMiLCJmaWxlIjoiLi9zcmMvbWFpbi9pbmRleC50cy5qcyIsInNvdXJjZXNDb250ZW50IjpbIi8vIGVzbGludC1kaXNhYmxlIGdsb2JhbC1yZXF1aXJlXG5pbXBvcnQgeyBhcHAsIGlwY01haW4sIE1lbnUgfSBmcm9tICdlbGVjdHJvbic7XG5pbXBvcnQgeyBjcmVhdGVSZW5kZXJlcldpbmRvdywgV2luZG93TmFtZSB9IGZyb20gJy4uL2NvbW1vbi93aW5kb3cnO1xuaW1wb3J0IHsgaGFuZGxlRXJyb3IgfSBmcm9tICcuL2Vycm9ycyc7XG5pbXBvcnQgeyBzZXRNZW51IH0gZnJvbSAnLi9tZW51JztcblxubGV0IG1haW5XaW5kb3cgPSBudWxsO1xubGV0IGJhY2tncm91bmRXaW5kb3cgPSBudWxsO1xuXG5jb25zdCBpbnN0YWxsRXh0ZW5zaW9ucyA9ICgpOiBQcm9taXNlPHZvaWQ+ID0+IHtcbiAgaWYgKHByb2Nlc3MuZW52Lk5PREVfRU5WID09PSAnZGV2ZWxvcG1lbnQnKSB7XG4gICAgY29uc3QgeyBkZWZhdWx0OiBpbnN0YWxsRXh0ZW5zaW9uLCBSRUFDVF9ERVZFTE9QRVJfVE9PTFMsIFJFRFVYX0RFVlRPT0xTIH0gPSByZXF1aXJlKCdlbGVjdHJvbi1kZXZ0b29scy1pbnN0YWxsZXInKTtcblxuICAgIGNvbnN0IGV4dGVuc2lvbnMgPSBbXG4gICAgICBSRUFDVF9ERVZFTE9QRVJfVE9PTFMsXG4gICAgICBSRURVWF9ERVZUT09MUyxcbiAgICBdO1xuXG4gICAgY29uc3QgZm9yY2VEb3dubG9hZCA9ICEhcHJvY2Vzcy5lbnYuVVBHUkFERV9FWFRFTlNJT05TO1xuICAgIHJldHVybiBQcm9taXNlLmFsbChleHRlbnNpb25zLm1hcChleHRlbnNpb24gPT4gaW5zdGFsbEV4dGVuc2lvbihleHRlbnNpb24uaWQsIGZvcmNlRG93bmxvYWQpKSlcbiAgICAgIC50aGVuKCgpID0+IHZvaWQgMCk7XG4gIH1cbiAgcmV0dXJuIFByb21pc2UucmVzb2x2ZSgpO1xufTtcblxucHJvY2Vzcy5vbigndW5jYXVnaHRFeGNlcHRpb24nLCBlcnJvciA9PiB7XG4gIGhhbmRsZUVycm9yKGVycm9yKTtcbn0pO1xuXG5hcHAub24oJ3JlYWR5JywgKCkgPT4gaW5zdGFsbEV4dGVuc2lvbnMoKS50aGVuKCgpID0+IHtcbiAgYmFja2dyb3VuZFdpbmRvdyA9IGNyZWF0ZVJlbmRlcmVyV2luZG93KHtcbiAgICBuYW1lOiBXaW5kb3dOYW1lLkJBQ0tHUk9VTkQsXG4gICAgc2hvdzogZmFsc2UsXG4gIH0pO1xuICBtYWluV2luZG93ID0gY3JlYXRlUmVuZGVyZXJXaW5kb3coe1xuICAgIHdpbmRvdzoge1xuICAgICAgd2lkdGg6IDEwMjQsXG4gICAgICBoZWlnaHQ6IDcyOCxcbiAgICB9LFxuICAgIHNob3c6IHRydWUsXG4gICAgbmFtZTogV2luZG93TmFtZS5BUFAsXG4gIH0pO1xuICBzZXRNZW51KG1haW5XaW5kb3cpO1xuICBtYWluV2luZG93Lm9uKCdjbG9zZWQnLCAoKSA9PiB7XG4gICAgbWFpbldpbmRvdyA9IG51bGw7XG4gICAgYmFja2dyb3VuZFdpbmRvdyA9IG51bGw7XG4gIH0pO1xuICBpZiAocHJvY2Vzcy5lbnYuTk9ERV9FTlYgPT09ICdwcm9kdWN0aW9uJykge1xuICAgIGNvbnN0IHNvdXJjZU1hcFN1cHBvcnQgPSByZXF1aXJlKCdzb3VyY2UtbWFwLXN1cHBvcnQnKTtcbiAgICBzb3VyY2VNYXBTdXBwb3J0Lmluc3RhbGwoKTtcbiAgfSBlbHNlIGlmIChwcm9jZXNzLmVudi5OT0RFX0VOViA9PT0gJ2RldmVsb3BtZW50Jykge1xuICAgIG1haW5XaW5kb3cub3BlbkRldlRvb2xzKCk7XG4gICAgbWFpbldpbmRvdy53ZWJDb250ZW50cy5vbignY29udGV4dC1tZW51JywgKF9lLCBwcm9wcykgPT4ge1xuICAgICAgY29uc3QgeyB4LCB5IH0gPSBwcm9wcztcbiAgICAgIE1lbnUuYnVpbGRGcm9tVGVtcGxhdGUoW1xuICAgICAgICB7XG4gICAgICAgICAgbGFiZWw6ICdJbnNwZWN0IGVsZW1lbnQnLFxuICAgICAgICAgIGNsaWNrOiAoKSA9PiBtYWluV2luZG93LndlYkNvbnRlbnRzLmluc3BlY3RFbGVtZW50KHgsIHkpLFxuICAgICAgICB9LFxuICAgICAgXSkucG9wdXAobWFpbldpbmRvdyk7XG4gICAgfSk7XG4gICAgcmVxdWlyZSgnZWxlY3Ryb24tZGVidWcnKSgpO1xuICAgIGNvbnN0IHBhdGggPSByZXF1aXJlKCdwYXRoJyk7XG4gICAgY29uc3QgcCA9IHBhdGguam9pbihfX2Rpcm5hbWUsICcuL25vZGVfbW9kdWxlcycpO1xuICAgIHJlcXVpcmUoJ21vZHVsZScpLmdsb2JhbFBhdGhzLnB1c2gocCk7XG4gIH1cbn0pKTtcblxuYXBwLm9uKCd3aW5kb3ctYWxsLWNsb3NlZCcsICgpID0+IHtcbiAgaWYgKHByb2Nlc3MucGxhdGZvcm0gIT09ICdkYXJ3aW4nKSB7XG4gICAgYXBwLnF1aXQoKTtcbiAgfVxufSk7XG5cbmlwY01haW4ub24oJ3JlbmRlcmVyJywgKGV2ZW50LCBwYXlsb2FkKSA9PiB7XG4gIGNvbnNvbGUubG9nKGV2ZW50KTtcbiAgY29uc29sZS5sb2cocGF5bG9hZCk7XG4gIG1haW5XaW5kb3cud2ViQ29udGVudHMuc2VuZCgnbWFpbicsIHBheWxvYWQpO1xufSk7XG5cbmlwY01haW4ub24oJ2JhY2tncm91bmQnLCAoZXZlbnQsIHBheWxvYWQpID0+IHtcbiAgY29uc29sZS5sb2coZXZlbnQpO1xuICBjb25zb2xlLmxvZyhwYXlsb2FkKTtcbiAgYmFja2dyb3VuZFdpbmRvdy53ZWJDb250ZW50cy5zZW5kKCdtYWluJywgcGF5bG9hZCk7XG59KTtcbiJdLCJzb3VyY2VSb290IjoiIn0=\n//# sourceURL=webpack-internal:///./src/main/index.ts\n");

/***/ }),

/***/ "./src/main/menu.ts":
/*!**************************!*\
  !*** ./src/main/menu.ts ***!
  \**************************/
/*! exports provided: setMenu */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, \"setMenu\", function() { return setMenu; });\n/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! electron */ \"electron\");\n/* harmony import */ var electron__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(electron__WEBPACK_IMPORTED_MODULE_0__);\n\nconst setMenu = (mainWindow) => {\n    const isMac = process.platform === 'darwin';\n    const cmd = isMac ? 'Command' : 'Ctrl';\n    const menu = electron__WEBPACK_IMPORTED_MODULE_0__[\"Menu\"].buildFromTemplate([\n        isMac ? {\n            label: 'Fuzzybase',\n            submenu: [\n                {\n                    label: 'About Fuzzybase',\n                    role: 'about',\n                }, {\n                    type: 'separator',\n                }, {\n                    label: 'Services',\n                    submenu: [],\n                }, {\n                    type: 'separator',\n                }, {\n                    label: 'Hide Fuzzybase',\n                    accelerator: 'Command+H',\n                    role: 'hide',\n                }, {\n                    label: 'Hide Others',\n                    accelerator: 'Command+Shift+H',\n                    role: 'hideOthers',\n                }, {\n                    label: 'Show All',\n                    role: 'front',\n                }, {\n                    type: 'separator',\n                }, {\n                    label: 'Quit',\n                    accelerator: 'Command+Q',\n                    role: 'quit',\n                },\n            ],\n        } : {\n            label: '&File',\n            submenu: [\n                {\n                    label: '&Close',\n                    accelerator: 'Ctrl+W',\n                    click() {\n                        mainWindow.close();\n                    },\n                },\n            ],\n        },\n        {\n            label: 'Edit',\n            submenu: [\n                {\n                    label: 'Undo',\n                    accelerator: 'Command+Z',\n                    role: 'undo',\n                }, {\n                    label: 'Redo',\n                    accelerator: 'Shift+Command+Z',\n                    role: 'redo',\n                }, {\n                    type: 'separator',\n                }, {\n                    label: 'Cut',\n                    accelerator: 'Command+X',\n                    role: 'cut',\n                }, {\n                    label: 'Copy',\n                    accelerator: 'Command+C',\n                    role: 'copy',\n                }, {\n                    label: 'Paste',\n                    accelerator: 'Command+V',\n                    role: 'paste',\n                }, {\n                    label: 'Select All',\n                    accelerator: 'Command+A',\n                    role: 'selectAll',\n                },\n            ],\n        },\n        {\n            label: '&View',\n            submenu: [\n                ...( true) ? [\n                    {\n                        label: '&Reload',\n                        accelerator: `${cmd}+R`,\n                        role: 'forceReload',\n                    }, {\n                        label: 'Toggle &Developer Tools',\n                        accelerator: `Alt+${cmd}+I`,\n                        role: 'toggleDevTools',\n                    },\n                ] : undefined,\n                {\n                    label: 'Toggle &Full Screen',\n                    accelerator: isMac ? 'Ctrl+Command+F' : 'F11',\n                    role: 'toggleFullScreen',\n                },\n            ],\n        },\n        isMac ? {\n            label: 'Window',\n            submenu: [\n                {\n                    label: 'Minimize',\n                    accelerator: 'Command+M',\n                    role: 'minimize',\n                }, {\n                    label: 'Close',\n                    accelerator: 'Command+W',\n                    role: 'close',\n                }, {\n                    type: 'separator',\n                }, {\n                    label: 'Bring All to Front',\n                    role: 'front',\n                },\n            ],\n        } : {},\n        {\n            label: 'Help',\n            submenu: [\n                {\n                    label: 'Search Issues',\n                    click() {\n                        electron__WEBPACK_IMPORTED_MODULE_0__[\"shell\"].openExternal('https://github.com/krzysztof-miemiec/fuzzybase/issues');\n                    },\n                },\n            ],\n        },\n    ]);\n    if (isMac) {\n        electron__WEBPACK_IMPORTED_MODULE_0__[\"Menu\"].setApplicationMenu(menu);\n    }\n    else {\n        mainWindow.setMenu(menu);\n    }\n};\n//# sourceURL=[module]\n//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJzb3VyY2VzIjpbIndlYnBhY2s6Ly8vLi9zcmMvbWFpbi9tZW51LnRzPzg0MjgiXSwibmFtZXMiOltdLCJtYXBwaW5ncyI6Ijs7OztBQUFzRDtBQUUvQyxNQUFNLE9BQU8sR0FBRyxDQUFDLFVBQXlCLEVBQUUsRUFBRTtJQUNuRCxNQUFNLEtBQUssR0FBRyxPQUFPLENBQUMsUUFBUSxLQUFLLFFBQVEsQ0FBQztJQUU1QyxNQUFNLEdBQUcsR0FBRyxLQUFLLENBQUMsQ0FBQyxDQUFDLFNBQVMsQ0FBQyxDQUFDLENBQUMsTUFBTSxDQUFDO0lBQ3ZDLE1BQU0sSUFBSSxHQUFHLDZDQUFJLENBQUMsaUJBQWlCLENBQUM7UUFDbEMsS0FBSyxDQUFDLENBQUMsQ0FBQztZQUNOLEtBQUssRUFBRSxXQUFXO1lBQ2xCLE9BQU8sRUFBRTtnQkFDUDtvQkFDRSxLQUFLLEVBQUUsaUJBQWlCO29CQUN4QixJQUFJLEVBQUUsT0FBTztpQkFDZCxFQUFFO29CQUNELElBQUksRUFBRSxXQUFXO2lCQUNsQixFQUFFO29CQUNELEtBQUssRUFBRSxVQUFVO29CQUNqQixPQUFPLEVBQUUsRUFBRTtpQkFDWixFQUFFO29CQUNELElBQUksRUFBRSxXQUFXO2lCQUNsQixFQUFFO29CQUNELEtBQUssRUFBRSxnQkFBZ0I7b0JBQ3ZCLFdBQVcsRUFBRSxXQUFXO29CQUN4QixJQUFJLEVBQUUsTUFBTTtpQkFDYixFQUFFO29CQUNELEtBQUssRUFBRSxhQUFhO29CQUNwQixXQUFXLEVBQUUsaUJBQWlCO29CQUM5QixJQUFJLEVBQUUsWUFBWTtpQkFDbkIsRUFBRTtvQkFDRCxLQUFLLEVBQUUsVUFBVTtvQkFDakIsSUFBSSxFQUFFLE9BQU87aUJBQ2QsRUFBRTtvQkFDRCxJQUFJLEVBQUUsV0FBVztpQkFDbEIsRUFBRTtvQkFDRCxLQUFLLEVBQUUsTUFBTTtvQkFDYixXQUFXLEVBQUUsV0FBVztvQkFDeEIsSUFBSSxFQUFFLE1BQU07aUJBQ2I7YUFDRjtTQUNGLENBQUMsQ0FBQyxDQUFDO1lBQ0YsS0FBSyxFQUFFLE9BQU87WUFDZCxPQUFPLEVBQUU7Z0JBQ1A7b0JBQ0UsS0FBSyxFQUFFLFFBQVE7b0JBQ2YsV0FBVyxFQUFFLFFBQVE7b0JBQ3JCLEtBQUs7d0JBQ0gsVUFBVSxDQUFDLEtBQUssRUFBRSxDQUFDO29CQUNyQixDQUFDO2lCQUNGO2FBQ0Y7U0FDRjtRQUNEO1lBQ0UsS0FBSyxFQUFFLE1BQU07WUFDYixPQUFPLEVBQUU7Z0JBQ1A7b0JBQ0UsS0FBSyxFQUFFLE1BQU07b0JBQ2IsV0FBVyxFQUFFLFdBQVc7b0JBQ3hCLElBQUksRUFBRSxNQUFNO2lCQUNiLEVBQUU7b0JBQ0QsS0FBSyxFQUFFLE1BQU07b0JBQ2IsV0FBVyxFQUFFLGlCQUFpQjtvQkFDOUIsSUFBSSxFQUFFLE1BQU07aUJBQ2IsRUFBRTtvQkFDRCxJQUFJLEVBQUUsV0FBVztpQkFDbEIsRUFBRTtvQkFDRCxLQUFLLEVBQUUsS0FBSztvQkFDWixXQUFXLEVBQUUsV0FBVztvQkFDeEIsSUFBSSxFQUFFLEtBQUs7aUJBQ1osRUFBRTtvQkFDRCxLQUFLLEVBQUUsTUFBTTtvQkFDYixXQUFXLEVBQUUsV0FBVztvQkFDeEIsSUFBSSxFQUFFLE1BQU07aUJBQ2IsRUFBRTtvQkFDRCxLQUFLLEVBQUUsT0FBTztvQkFDZCxXQUFXLEVBQUUsV0FBVztvQkFDeEIsSUFBSSxFQUFFLE9BQU87aUJBQ2QsRUFBRTtvQkFDRCxLQUFLLEVBQUUsWUFBWTtvQkFDbkIsV0FBVyxFQUFFLFdBQVc7b0JBQ3hCLElBQUksRUFBRSxXQUFXO2lCQUNsQjthQUNGO1NBQ0Y7UUFDRDtZQUNFLEtBQUssRUFBRSxPQUFPO1lBQ2QsT0FBTyxFQUFFO2dCQUNQLEdBQUcsQ0FBQyxLQUFzQyxDQUFDLENBQUMsQ0FBQyxDQUFDO29CQUM1Qzt3QkFDRSxLQUFLLEVBQUUsU0FBUzt3QkFDaEIsV0FBVyxFQUFFLEdBQUcsR0FBRyxJQUFJO3dCQUN2QixJQUFJLEVBQUUsYUFBYTtxQkFDcEIsRUFBRTt3QkFDRCxLQUFLLEVBQUUseUJBQXlCO3dCQUNoQyxXQUFXLEVBQUUsT0FBTyxHQUFHLElBQUk7d0JBQzNCLElBQUksRUFBRSxnQkFBZ0I7cUJBQ3ZCO2lCQUNGLENBQUMsQ0FBQyxDQUFDLFNBQUU7Z0JBQ047b0JBQ0UsS0FBSyxFQUFFLHFCQUFxQjtvQkFDNUIsV0FBVyxFQUFFLEtBQUssQ0FBQyxDQUFDLENBQUMsZ0JBQWdCLENBQUMsQ0FBQyxDQUFDLEtBQUs7b0JBQzdDLElBQUksRUFBRSxrQkFBa0I7aUJBQ3pCO2FBQ0Y7U0FDRjtRQUNELEtBQUssQ0FBQyxDQUFDLENBQUM7WUFDTixLQUFLLEVBQUUsUUFBUTtZQUNmLE9BQU8sRUFBRTtnQkFDUDtvQkFDRSxLQUFLLEVBQUUsVUFBVTtvQkFDakIsV0FBVyxFQUFFLFdBQVc7b0JBQ3hCLElBQUksRUFBRSxVQUFVO2lCQUNqQixFQUFFO29CQUNELEtBQUssRUFBRSxPQUFPO29CQUNkLFdBQVcsRUFBRSxXQUFXO29CQUN4QixJQUFJLEVBQUUsT0FBTztpQkFDZCxFQUFFO29CQUNELElBQUksRUFBRSxXQUFXO2lCQUNsQixFQUFFO29CQUNELEtBQUssRUFBRSxvQkFBb0I7b0JBQzNCLElBQUksRUFBRSxPQUFPO2lCQUNkO2FBQ0Y7U0FDRixDQUFDLENBQUMsQ0FBQyxFQUFFO1FBQ047WUFDRSxLQUFLLEVBQUUsTUFBTTtZQUNiLE9BQU8sRUFBRTtnQkFDUDtvQkFDRSxLQUFLLEVBQUUsZUFBZTtvQkFDdEIsS0FBSzt3QkFDSCw4Q0FBSyxDQUFDLFlBQVksQ0FBQyx1REFBdUQsQ0FBQyxDQUFDO29CQUM5RSxDQUFDO2lCQUNGO2FBQ0Y7U0FDRjtLQUNGLENBQUMsQ0FBQztJQUNILElBQUksS0FBSyxFQUFFO1FBQ1QsNkNBQUksQ0FBQyxrQkFBa0IsQ0FBQyxJQUFJLENBQUMsQ0FBQztLQUMvQjtTQUFNO1FBQ0wsVUFBVSxDQUFDLE9BQU8sQ0FBQyxJQUFJLENBQUMsQ0FBQztLQUMxQjtBQUNILENBQUMsQ0FBQyIsImZpbGUiOiIuL3NyYy9tYWluL21lbnUudHMuanMiLCJzb3VyY2VzQ29udGVudCI6WyJpbXBvcnQgeyBCcm93c2VyV2luZG93LCBNZW51LCBzaGVsbCB9IGZyb20gJ2VsZWN0cm9uJztcblxuZXhwb3J0IGNvbnN0IHNldE1lbnUgPSAobWFpbldpbmRvdzogQnJvd3NlcldpbmRvdykgPT4ge1xuICBjb25zdCBpc01hYyA9IHByb2Nlc3MucGxhdGZvcm0gPT09ICdkYXJ3aW4nO1xuXG4gIGNvbnN0IGNtZCA9IGlzTWFjID8gJ0NvbW1hbmQnIDogJ0N0cmwnO1xuICBjb25zdCBtZW51ID0gTWVudS5idWlsZEZyb21UZW1wbGF0ZShbXG4gICAgaXNNYWMgPyB7XG4gICAgICBsYWJlbDogJ0Z1enp5YmFzZScsXG4gICAgICBzdWJtZW51OiBbXG4gICAgICAgIHtcbiAgICAgICAgICBsYWJlbDogJ0Fib3V0IEZ1enp5YmFzZScsXG4gICAgICAgICAgcm9sZTogJ2Fib3V0JyxcbiAgICAgICAgfSwge1xuICAgICAgICAgIHR5cGU6ICdzZXBhcmF0b3InLFxuICAgICAgICB9LCB7XG4gICAgICAgICAgbGFiZWw6ICdTZXJ2aWNlcycsXG4gICAgICAgICAgc3VibWVudTogW10sXG4gICAgICAgIH0sIHtcbiAgICAgICAgICB0eXBlOiAnc2VwYXJhdG9yJyxcbiAgICAgICAgfSwge1xuICAgICAgICAgIGxhYmVsOiAnSGlkZSBGdXp6eWJhc2UnLFxuICAgICAgICAgIGFjY2VsZXJhdG9yOiAnQ29tbWFuZCtIJyxcbiAgICAgICAgICByb2xlOiAnaGlkZScsXG4gICAgICAgIH0sIHtcbiAgICAgICAgICBsYWJlbDogJ0hpZGUgT3RoZXJzJyxcbiAgICAgICAgICBhY2NlbGVyYXRvcjogJ0NvbW1hbmQrU2hpZnQrSCcsXG4gICAgICAgICAgcm9sZTogJ2hpZGVPdGhlcnMnLFxuICAgICAgICB9LCB7XG4gICAgICAgICAgbGFiZWw6ICdTaG93IEFsbCcsXG4gICAgICAgICAgcm9sZTogJ2Zyb250JyxcbiAgICAgICAgfSwge1xuICAgICAgICAgIHR5cGU6ICdzZXBhcmF0b3InLFxuICAgICAgICB9LCB7XG4gICAgICAgICAgbGFiZWw6ICdRdWl0JyxcbiAgICAgICAgICBhY2NlbGVyYXRvcjogJ0NvbW1hbmQrUScsXG4gICAgICAgICAgcm9sZTogJ3F1aXQnLFxuICAgICAgICB9LFxuICAgICAgXSxcbiAgICB9IDoge1xuICAgICAgbGFiZWw6ICcmRmlsZScsXG4gICAgICBzdWJtZW51OiBbXG4gICAgICAgIHtcbiAgICAgICAgICBsYWJlbDogJyZDbG9zZScsXG4gICAgICAgICAgYWNjZWxlcmF0b3I6ICdDdHJsK1cnLFxuICAgICAgICAgIGNsaWNrKCkge1xuICAgICAgICAgICAgbWFpbldpbmRvdy5jbG9zZSgpO1xuICAgICAgICAgIH0sXG4gICAgICAgIH0sXG4gICAgICBdLFxuICAgIH0sXG4gICAge1xuICAgICAgbGFiZWw6ICdFZGl0JyxcbiAgICAgIHN1Ym1lbnU6IFtcbiAgICAgICAge1xuICAgICAgICAgIGxhYmVsOiAnVW5kbycsXG4gICAgICAgICAgYWNjZWxlcmF0b3I6ICdDb21tYW5kK1onLFxuICAgICAgICAgIHJvbGU6ICd1bmRvJyxcbiAgICAgICAgfSwge1xuICAgICAgICAgIGxhYmVsOiAnUmVkbycsXG4gICAgICAgICAgYWNjZWxlcmF0b3I6ICdTaGlmdCtDb21tYW5kK1onLFxuICAgICAgICAgIHJvbGU6ICdyZWRvJyxcbiAgICAgICAgfSwge1xuICAgICAgICAgIHR5cGU6ICdzZXBhcmF0b3InLFxuICAgICAgICB9LCB7XG4gICAgICAgICAgbGFiZWw6ICdDdXQnLFxuICAgICAgICAgIGFjY2VsZXJhdG9yOiAnQ29tbWFuZCtYJyxcbiAgICAgICAgICByb2xlOiAnY3V0JyxcbiAgICAgICAgfSwge1xuICAgICAgICAgIGxhYmVsOiAnQ29weScsXG4gICAgICAgICAgYWNjZWxlcmF0b3I6ICdDb21tYW5kK0MnLFxuICAgICAgICAgIHJvbGU6ICdjb3B5JyxcbiAgICAgICAgfSwge1xuICAgICAgICAgIGxhYmVsOiAnUGFzdGUnLFxuICAgICAgICAgIGFjY2VsZXJhdG9yOiAnQ29tbWFuZCtWJyxcbiAgICAgICAgICByb2xlOiAncGFzdGUnLFxuICAgICAgICB9LCB7XG4gICAgICAgICAgbGFiZWw6ICdTZWxlY3QgQWxsJyxcbiAgICAgICAgICBhY2NlbGVyYXRvcjogJ0NvbW1hbmQrQScsXG4gICAgICAgICAgcm9sZTogJ3NlbGVjdEFsbCcsXG4gICAgICAgIH0sXG4gICAgICBdLFxuICAgIH0sXG4gICAge1xuICAgICAgbGFiZWw6ICcmVmlldycsXG4gICAgICBzdWJtZW51OiBbXG4gICAgICAgIC4uLihwcm9jZXNzLmVudi5OT0RFX0VOViA9PT0gJ2RldmVsb3BtZW50JykgPyBbXG4gICAgICAgICAge1xuICAgICAgICAgICAgbGFiZWw6ICcmUmVsb2FkJyxcbiAgICAgICAgICAgIGFjY2VsZXJhdG9yOiBgJHtjbWR9K1JgLFxuICAgICAgICAgICAgcm9sZTogJ2ZvcmNlUmVsb2FkJyxcbiAgICAgICAgICB9LCB7XG4gICAgICAgICAgICBsYWJlbDogJ1RvZ2dsZSAmRGV2ZWxvcGVyIFRvb2xzJyxcbiAgICAgICAgICAgIGFjY2VsZXJhdG9yOiBgQWx0KyR7Y21kfStJYCxcbiAgICAgICAgICAgIHJvbGU6ICd0b2dnbGVEZXZUb29scycsXG4gICAgICAgICAgfSxcbiAgICAgICAgXSA6IFtdLFxuICAgICAgICB7XG4gICAgICAgICAgbGFiZWw6ICdUb2dnbGUgJkZ1bGwgU2NyZWVuJyxcbiAgICAgICAgICBhY2NlbGVyYXRvcjogaXNNYWMgPyAnQ3RybCtDb21tYW5kK0YnIDogJ0YxMScsXG4gICAgICAgICAgcm9sZTogJ3RvZ2dsZUZ1bGxTY3JlZW4nLFxuICAgICAgICB9LFxuICAgICAgXSxcbiAgICB9LFxuICAgIGlzTWFjID8ge1xuICAgICAgbGFiZWw6ICdXaW5kb3cnLFxuICAgICAgc3VibWVudTogW1xuICAgICAgICB7XG4gICAgICAgICAgbGFiZWw6ICdNaW5pbWl6ZScsXG4gICAgICAgICAgYWNjZWxlcmF0b3I6ICdDb21tYW5kK00nLFxuICAgICAgICAgIHJvbGU6ICdtaW5pbWl6ZScsXG4gICAgICAgIH0sIHtcbiAgICAgICAgICBsYWJlbDogJ0Nsb3NlJyxcbiAgICAgICAgICBhY2NlbGVyYXRvcjogJ0NvbW1hbmQrVycsXG4gICAgICAgICAgcm9sZTogJ2Nsb3NlJyxcbiAgICAgICAgfSwge1xuICAgICAgICAgIHR5cGU6ICdzZXBhcmF0b3InLFxuICAgICAgICB9LCB7XG4gICAgICAgICAgbGFiZWw6ICdCcmluZyBBbGwgdG8gRnJvbnQnLFxuICAgICAgICAgIHJvbGU6ICdmcm9udCcsXG4gICAgICAgIH0sXG4gICAgICBdLFxuICAgIH0gOiB7fSxcbiAgICB7XG4gICAgICBsYWJlbDogJ0hlbHAnLFxuICAgICAgc3VibWVudTogW1xuICAgICAgICB7XG4gICAgICAgICAgbGFiZWw6ICdTZWFyY2ggSXNzdWVzJyxcbiAgICAgICAgICBjbGljaygpIHtcbiAgICAgICAgICAgIHNoZWxsLm9wZW5FeHRlcm5hbCgnaHR0cHM6Ly9naXRodWIuY29tL2tyenlzenRvZi1taWVtaWVjL2Z1enp5YmFzZS9pc3N1ZXMnKTtcbiAgICAgICAgICB9LFxuICAgICAgICB9LFxuICAgICAgXSxcbiAgICB9LFxuICBdKTtcbiAgaWYgKGlzTWFjKSB7XG4gICAgTWVudS5zZXRBcHBsaWNhdGlvbk1lbnUobWVudSk7XG4gIH0gZWxzZSB7XG4gICAgbWFpbldpbmRvdy5zZXRNZW51KG1lbnUpO1xuICB9XG59O1xuIl0sInNvdXJjZVJvb3QiOiIifQ==\n//# sourceURL=webpack-internal:///./src/main/menu.ts\n");

/***/ }),

/***/ 0:
/*!************************************************************************************************!*\
  !*** multi ./node_modules/electron-webpack/out/electron-main-hmr/main-hmr ./src/main/index.ts ***!
  \************************************************************************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

__webpack_require__(/*! /Projects/fuzzybase/node_modules/electron-webpack/out/electron-main-hmr/main-hmr */"./node_modules/electron-webpack/out/electron-main-hmr/main-hmr.js");
module.exports = __webpack_require__(/*! /Projects/fuzzybase/src/main/index.ts */"./src/main/index.ts");


/***/ }),

/***/ "electron":
/*!***************************!*\
  !*** external "electron" ***!
  \***************************/
/*! no static exports found */
/***/ (function(module, exports) {

eval("module.exports = require(\"electron\");//# sourceURL=[module]\n//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJzb3VyY2VzIjpbIndlYnBhY2s6Ly8vZXh0ZXJuYWwgXCJlbGVjdHJvblwiPzA0ZjMiXSwibmFtZXMiOltdLCJtYXBwaW5ncyI6IkFBQUEiLCJmaWxlIjoiZWxlY3Ryb24uanMiLCJzb3VyY2VzQ29udGVudCI6WyJtb2R1bGUuZXhwb3J0cyA9IHJlcXVpcmUoXCJlbGVjdHJvblwiKTsiXSwic291cmNlUm9vdCI6IiJ9\n//# sourceURL=webpack-internal:///electron\n");

/***/ }),

/***/ "electron-debug":
/*!*********************************!*\
  !*** external "electron-debug" ***!
  \*********************************/
/*! no static exports found */
/***/ (function(module, exports) {

eval("module.exports = require(\"electron-debug\");//# sourceURL=[module]\n//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJzb3VyY2VzIjpbIndlYnBhY2s6Ly8vZXh0ZXJuYWwgXCJlbGVjdHJvbi1kZWJ1Z1wiPzk4MjIiXSwibmFtZXMiOltdLCJtYXBwaW5ncyI6IkFBQUEiLCJmaWxlIjoiZWxlY3Ryb24tZGVidWcuanMiLCJzb3VyY2VzQ29udGVudCI6WyJtb2R1bGUuZXhwb3J0cyA9IHJlcXVpcmUoXCJlbGVjdHJvbi1kZWJ1Z1wiKTsiXSwic291cmNlUm9vdCI6IiJ9\n//# sourceURL=webpack-internal:///electron-debug\n");

/***/ }),

/***/ "electron-devtools-installer":
/*!**********************************************!*\
  !*** external "electron-devtools-installer" ***!
  \**********************************************/
/*! no static exports found */
/***/ (function(module, exports) {

eval("module.exports = require(\"electron-devtools-installer\");//# sourceURL=[module]\n//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJzb3VyY2VzIjpbIndlYnBhY2s6Ly8vZXh0ZXJuYWwgXCJlbGVjdHJvbi1kZXZ0b29scy1pbnN0YWxsZXJcIj9jZThjIl0sIm5hbWVzIjpbXSwibWFwcGluZ3MiOiJBQUFBIiwiZmlsZSI6ImVsZWN0cm9uLWRldnRvb2xzLWluc3RhbGxlci5qcyIsInNvdXJjZXNDb250ZW50IjpbIm1vZHVsZS5leHBvcnRzID0gcmVxdWlyZShcImVsZWN0cm9uLWRldnRvb2xzLWluc3RhbGxlclwiKTsiXSwic291cmNlUm9vdCI6IiJ9\n//# sourceURL=webpack-internal:///electron-devtools-installer\n");

/***/ }),

/***/ "electron-webpack/out/electron-main-hmr/HmrClient":
/*!*******************************************************************!*\
  !*** external "electron-webpack/out/electron-main-hmr/HmrClient" ***!
  \*******************************************************************/
/*! no static exports found */
/***/ (function(module, exports) {

eval("module.exports = require(\"electron-webpack/out/electron-main-hmr/HmrClient\");//# sourceURL=[module]\n//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJzb3VyY2VzIjpbIndlYnBhY2s6Ly8vZXh0ZXJuYWwgXCJlbGVjdHJvbi13ZWJwYWNrL291dC9lbGVjdHJvbi1tYWluLWhtci9IbXJDbGllbnRcIj9kZTY3Il0sIm5hbWVzIjpbXSwibWFwcGluZ3MiOiJBQUFBIiwiZmlsZSI6ImVsZWN0cm9uLXdlYnBhY2svb3V0L2VsZWN0cm9uLW1haW4taG1yL0htckNsaWVudC5qcyIsInNvdXJjZXNDb250ZW50IjpbIm1vZHVsZS5leHBvcnRzID0gcmVxdWlyZShcImVsZWN0cm9uLXdlYnBhY2svb3V0L2VsZWN0cm9uLW1haW4taG1yL0htckNsaWVudFwiKTsiXSwic291cmNlUm9vdCI6IiJ9\n//# sourceURL=webpack-internal:///electron-webpack/out/electron-main-hmr/HmrClient\n");

/***/ }),

/***/ "module":
/*!*************************!*\
  !*** external "module" ***!
  \*************************/
/*! no static exports found */
/***/ (function(module, exports) {

eval("module.exports = require(\"module\");//# sourceURL=[module]\n//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJzb3VyY2VzIjpbIndlYnBhY2s6Ly8vZXh0ZXJuYWwgXCJtb2R1bGVcIj83YzQ4Il0sIm5hbWVzIjpbXSwibWFwcGluZ3MiOiJBQUFBIiwiZmlsZSI6Im1vZHVsZS5qcyIsInNvdXJjZXNDb250ZW50IjpbIm1vZHVsZS5leHBvcnRzID0gcmVxdWlyZShcIm1vZHVsZVwiKTsiXSwic291cmNlUm9vdCI6IiJ9\n//# sourceURL=webpack-internal:///module\n");

/***/ }),

/***/ "path":
/*!***********************!*\
  !*** external "path" ***!
  \***********************/
/*! no static exports found */
/***/ (function(module, exports) {

eval("module.exports = require(\"path\");//# sourceURL=[module]\n//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJzb3VyY2VzIjpbIndlYnBhY2s6Ly8vZXh0ZXJuYWwgXCJwYXRoXCI/NzRiYiJdLCJuYW1lcyI6W10sIm1hcHBpbmdzIjoiQUFBQSIsImZpbGUiOiJwYXRoLmpzIiwic291cmNlc0NvbnRlbnQiOlsibW9kdWxlLmV4cG9ydHMgPSByZXF1aXJlKFwicGF0aFwiKTsiXSwic291cmNlUm9vdCI6IiJ9\n//# sourceURL=webpack-internal:///path\n");

/***/ }),

/***/ "raven-js":
/*!***************************!*\
  !*** external "raven-js" ***!
  \***************************/
/*! no static exports found */
/***/ (function(module, exports) {

eval("module.exports = require(\"raven-js\");//# sourceURL=[module]\n//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJzb3VyY2VzIjpbIndlYnBhY2s6Ly8vZXh0ZXJuYWwgXCJyYXZlbi1qc1wiP2EyMTIiXSwibmFtZXMiOltdLCJtYXBwaW5ncyI6IkFBQUEiLCJmaWxlIjoicmF2ZW4tanMuanMiLCJzb3VyY2VzQ29udGVudCI6WyJtb2R1bGUuZXhwb3J0cyA9IHJlcXVpcmUoXCJyYXZlbi1qc1wiKTsiXSwic291cmNlUm9vdCI6IiJ9\n//# sourceURL=webpack-internal:///raven-js\n");

/***/ }),

/***/ "source-map-support/source-map-support.js":
/*!***********************************************************!*\
  !*** external "source-map-support/source-map-support.js" ***!
  \***********************************************************/
/*! no static exports found */
/***/ (function(module, exports) {

eval("module.exports = require(\"source-map-support/source-map-support.js\");//# sourceURL=[module]\n//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJzb3VyY2VzIjpbIndlYnBhY2s6Ly8vZXh0ZXJuYWwgXCJzb3VyY2UtbWFwLXN1cHBvcnQvc291cmNlLW1hcC1zdXBwb3J0LmpzXCI/OWM1ZiJdLCJuYW1lcyI6W10sIm1hcHBpbmdzIjoiQUFBQSIsImZpbGUiOiJzb3VyY2UtbWFwLXN1cHBvcnQvc291cmNlLW1hcC1zdXBwb3J0LmpzLmpzIiwic291cmNlc0NvbnRlbnQiOlsibW9kdWxlLmV4cG9ydHMgPSByZXF1aXJlKFwic291cmNlLW1hcC1zdXBwb3J0L3NvdXJjZS1tYXAtc3VwcG9ydC5qc1wiKTsiXSwic291cmNlUm9vdCI6IiJ9\n//# sourceURL=webpack-internal:///source-map-support/source-map-support.js\n");

/***/ })

/******/ });