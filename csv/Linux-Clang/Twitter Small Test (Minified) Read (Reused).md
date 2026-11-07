
----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2435.29 | 0.0709175 | 121.252ms | 2889 | 160 | 102.996 | 1131.35 | 0.0684553 | 0.993188 | 1(Win) | true |
| Jsonifier (two-stage) | 2411.65 | 0.0285732 | 122.149ms | 2889 | 640 | 68.1964 | 1142.44 | 0.000820607 | 1.00323 | 2(Loss) | true |
| Glaze | 2267.91 | 0.343723 | 128.771ms | 2889 | 40 | 697.464 | 1214.85 | 0.234048 | 1.06688 | 3(Loss) | true |
| simdjson (ondemand) | 1061.51 | 0.0549718 | 269.045ms | 2889 | 80 | 162.861 | 2595.51 | 0.0293863 | 2.30681 | 4(Loss) | true |
