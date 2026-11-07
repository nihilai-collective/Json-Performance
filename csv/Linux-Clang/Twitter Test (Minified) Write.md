
----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17322.5 | 0.158561 | 2624.54ms | 475954 | 1280 | 2.2096e+06 | 26203.2 | 0.00120752 | 0.142769 | 1(Win) | true |
| Glaze | 5811.07 | 0.0989282 | 7808.87ms | 475954 | 2560 | 1.52862e+07 | 78110.5 | 0.0560618 | 0.425865 | 2(Loss) | true |
