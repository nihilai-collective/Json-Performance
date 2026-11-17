
----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1352.97 | 0.0478673 | 1027.61ms | 4390 | 2560 | 5616.56 | 3094.4 | 0.0582493 | 3.84988 | 17.6444 | 3.28907 | 0.00147752 | 8.37308e-05 | 3.07873e-05 | 1(Win) | true |
| simdjson (ondemand) | 1066.32 | 0.0534554 | 1107.52ms | 4390 | 640 | 2819.14 | 3926.24 | 0.00795863 | 4.89969 | 19.6932 | 3.64624 | 0.00394647 | 2.66942e-05 | 2.49146e-06 | 2(Loss) | true |
