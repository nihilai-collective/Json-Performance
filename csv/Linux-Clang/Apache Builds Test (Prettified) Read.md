
----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2037.79 | 0.111274 | 5833.95ms | 124597 | 1280 | 5.38881e+06 | 58310.8 | 0.021372 | 1.2144 | 1(Win) | true |
| Jsonifier (two-stage) | 1754.84 | 0.100902 | 6812.31ms | 124597 | 640 | 2.98759e+06 | 67712.8 | 0.00840566 | 1.4103 | 2(Loss) | true |
| Glaze | 1703.75 | 0.0395075 | 6989.81ms | 124597 | 4890 | 3.71254e+06 | 69743.2 | 0.0465803 | 1.45261 | 3(Loss) | true |
| simdjson (ondemand) | 1445.52 | 0.0574763 | 8238.9ms | 124597 | 2560 | 5.71459e+06 | 82202.2 | 0.0983034 | 1.7122 | 4(Loss) | true |
