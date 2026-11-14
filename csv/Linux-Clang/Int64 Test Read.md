
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 742.524 | 0.203345 | 500.903ms | 3862 | 1280 | 130221 | 4960.23 | 0.0974778 | 3.3154 | 1(Win) | true |
| simdjson (ondemand) | 650.774 | 0.0366886 | 575.074ms | 3862 | 40 | 172.459 | 5659.55 | 0.04154 | 3.78622 | 2(Loss) | true |
