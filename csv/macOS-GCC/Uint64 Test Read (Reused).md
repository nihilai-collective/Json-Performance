
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2969.12 | 1.47933 | 145.828ms | 3873 | 640 | 216745 | 1244 | 0.51713 | 1(Win) | true |
| Glaze | 1240.46 | 1.1207 | 267.329ms | 3873 | 320 | 356337 | 2977.6 | 0.485961 | 2(Loss) | true |
| Jsonifier (two-stage) | 834.18 | 0.489413 | 457.91ms | 3873 | 1280 | 601086 | 4427.8 | 0.00451712 | 3(Loss) | true |
| simdjson (ondemand) | 453.712 | 0.774694 | 918.38ms | 3873 | 30 | 119321 | 8140.8 | 0.845666 | 4(Loss) | true |
