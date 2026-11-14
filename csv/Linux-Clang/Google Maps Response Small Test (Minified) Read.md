
----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1302.84 | 0.0453781 | 1040.64ms | 4390 | 1280 | 2721.78 | 3213.47 | 0.0318828 | 4.00204 | 18.0189 | 3.50228 | 0.00251904 | 5.44562e-05 | 1.61945e-05 | 1(Win) | true |
| simdjson (ondemand) | 1044.97 | 0.0221148 | 1117.89ms | 4390 | 4890 | 3838.8 | 4006.45 | 0.0196257 | 4.97757 | 20.6995 | 3.58132 | 0.00438219 | 5.47349e-05 | 1.23911e-05 | 2(Loss) | true |
