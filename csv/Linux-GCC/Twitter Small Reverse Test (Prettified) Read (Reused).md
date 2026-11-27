
----
### Twitter Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1109.65 | 0.107737 | 1054.26ms | 3770 | 320 | 3899.31 | 3240.07 | 0.016206 | 4.70142 | 19.3332 | 3.51671 | 0.00246021 | 5.80239e-05 | 2.65252e-05 | 1(Win) | true |
| simdjson (ondemand) | 527.021 | 0.0554092 | 1409.59ms | 3770 | 640 | 9144.73 | 6822.03 | 0.0382868 | 9.82692 | 43.4554 | 8.68356 | 0.00891868 | 9.03515e-05 | 5.42938e-05 | 2(Loss) | true |
