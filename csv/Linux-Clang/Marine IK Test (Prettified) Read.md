
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2640.97 | 0.11089 | 8302.72ms | 7351818 | 30 | 2.59998e+08 | 2.65479e+06 | 0.236913 | 0.937444 | 1(Win) | true |
| Jsonifier | 2454.97 | 0.198645 | 8857.72ms | 7351818 | 160 | 5.14956e+09 | 2.85593e+06 | 0.056928 | 1.00847 | 2(Loss) | true |
| simdjson (ondemand) | 2171.17 | 0.0782711 | 9962.11ms | 7351818 | 40 | 2.55544e+08 | 3.22925e+06 | 0.0616785 | 1.1403 | 3(Loss) | true |
| Glaze | 2073.62 | 0.0617996 | 5122.36ms | 7351818 | 30 | 1.30985e+08 | 3.38115e+06 | 0.495132 | 1.19394 | 4(Loss) | true |
