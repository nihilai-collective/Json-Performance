
----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 823.431 | 0.186979 | 6145.66ms | 409725 | 30 | 2.36177e+07 | 474532 | 0.0141985 | 6.16654 | 28.7842 | 5.82221 | 0.0143735 | 0.0239285 | 5.1742e-05 | 1(Win) | true |
| simdjson (ondemand) | 481.664 | 0.0647706 | 5216.07ms | 409725 | 160 | 4.41746e+07 | 811238 | 0.151627 | 10.6335 | 46.7674 | 9.42949 | 0.0352755 | 0.0393142 | 2.54286e-05 | 2(Loss) | true |
