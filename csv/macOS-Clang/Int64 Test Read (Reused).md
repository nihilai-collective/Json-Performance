
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2775.29 | 0.212441 | 136.856ms | 3862 | 40 | 317.938 | 1327.1 | 0.0502601 | 1(Win) | true |
| Glaze | 1569.12 | 0.230711 | 257.601ms | 3862 | 30 | 879.771 | 2347.23 | 0.112063 | 2(Loss) | true |
| Jsonifier (two-stage) | 938.373 | 0.127339 | 400.86ms | 3862 | 40 | 999.204 | 3924.97 | 0.0690502 | 3(Loss) | true |
| simdjson (ondemand) | 481.8 | 0.0892611 | 765.394ms | 3862 | 30 | 1396.81 | 7644.43 | 0.0727669 | 4(Loss) | true |
