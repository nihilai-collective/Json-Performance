
----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1903.22 | 0.0484115 | 6305.02ms | 124597 | 4890 | 4.46731e+06 | 62433.8 | 0.358614 | 1.30028 | 1(Win) | true |
| Jsonifier | 1743.22 | 0.0442815 | 6853.86ms | 124597 | 4890 | 4.45517e+06 | 68164.1 | 0.256284 | 1.41968 | 2(Loss) | true |
| Glaze | 1612.52 | 0.0937818 | 7408.84ms | 124597 | 1280 | 6.11297e+06 | 73689 | 0.733722 | 1.5348 | 3(Loss) | true |
| simdjson (ondemand) | 1406.32 | 0.157977 | 8500.09ms | 124597 | 160 | 2.85074e+06 | 84493.7 | 0.0893913 | 1.75993 | 4(Loss) | true |
