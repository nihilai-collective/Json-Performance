
----
### Twitter Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 702.103 | 0.174978 | 387.087ms | 2821 | 1280 | 57541.7 | 3831.8 | 0.213623 | 4.30756 | 1(Win) | true |
| simdjson (ondemand) | 284.581 | 0.188431 | 998.578ms | 2821 | 640 | 203086 | 9453.59 | 0.603592 | 10.6616 | 2(Loss) | true |
