
----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3911.63 | 0.10556 | 110.687ms | 3862 | 4890 | 4830.82 | 941.575 | 0.189189 | 0.755385 | 1(Win) | true |
| Glaze | 1653.25 | 0.0955348 | 256.656ms | 3862 | 4890 | 22150.4 | 2227.79 | 0.332984 | 1.81835 | 2(Loss) | true |
