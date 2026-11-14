
----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1738.24 | 0.22917 | 6918.06ms | 124597 | 320 | 7.8535e+06 | 68359.4 | 0.506921 | 1.42371 | 1(Win) | true |
| simdjson (ondemand) | 1520.48 | 0.0459699 | 7854.7ms | 124597 | 4890 | 6.31113e+06 | 78149.4 | 0.199647 | 1.62772 | 2(Loss) | true |
