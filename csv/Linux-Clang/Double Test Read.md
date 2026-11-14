
----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1949.62 | 0.214626 | 93.332ms | 1811 | 640 | 2313.57 | 885.867 | 0.65656 | 1.22595 | 1(Win) | true |
| simdjson (stage-1) | 959.01 | 0.0741216 | 184.17ms | 1811 | 80 | 142.551 | 1800.92 | 0.109786 | 2.54163 | 2(Loss) | true |
