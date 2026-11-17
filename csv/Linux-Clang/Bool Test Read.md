
----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1122.52 | 0.334264 | 88.9808ms | 905 | 4890 | 32299.6 | 768.874 | 0.0468392 | 2.12916 | 1(Win) | true |
| simdjson (stage-1) | 521.443 | 0.128803 | 170.954ms | 905 | 30 | 136.351 | 1655.17 | 0.0603804 | 4.67978 | 2(Loss) | true |
