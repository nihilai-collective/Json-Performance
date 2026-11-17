
----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1628.19 | 0.159757 | 60.2209ms | 905 | 4890 | 3506.85 | 530.082 | 0.0670605 | 1.80118 | 1(Win) | true |
| Glaze | 548.351 | 0.154275 | 173.585ms | 905 | 4890 | 28832.2 | 1573.95 | 0.057211 | 5.4752 | 2(Loss) | true |
