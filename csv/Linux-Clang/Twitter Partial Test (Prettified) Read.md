
----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11628.5 | 0.339293 | 5317.33ms | 631514 | 80 | 2.47035e+06 | 51791.6 | 0.173568 | 0.212728 | 1(Win) | true |
| Jsonifier (two-stage) | 11510.1 | 0.0963502 | 5246.01ms | 631514 | 1280 | 3.25326e+06 | 52324.2 | 0.0805205 | 0.214927 | 2(Loss) | true |
| simdjson (ondemand) | 9615.43 | 0.123815 | 6295.98ms | 631514 | 640 | 3.84905e+06 | 62634.6 | 0.181952 | 0.257306 | 3(Loss) | true |
| Glaze | 4246.97 | 0.0391948 | 7254.27ms | 631514 | 2560 | 7.90868e+06 | 141809 | 0.0661617 | 0.582852 | 4(Loss) | true |
