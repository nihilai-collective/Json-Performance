
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3186.89 | 0.0511534 | 118.889ms | 3862 | 80 | 27.9595 | 1155.7 | 0.108277 | 0.75837 | 1(Win) | true |
| Glaze | 1598.17 | 0.0419955 | 239.445ms | 3862 | 80 | 74.9328 | 2304.56 | 0.244026 | 1.53339 | 2(Loss) | true |
| Jsonifier (two-stage) | 809.197 | 0.0382243 | 460.164ms | 3862 | 80 | 242.15 | 4551.54 | 0.060657 | 3.04137 | 3(Loss) | true |
| simdjson (ondemand) | 578.117 | 0.123083 | 641.835ms | 3862 | 4890 | 300678 | 6370.84 | 0.0482283 | 4.26477 | 4(Loss) | true |
