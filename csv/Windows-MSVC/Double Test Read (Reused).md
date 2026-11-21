
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1111.28 | 0.313823 | 158.9ms | 1811 | 4890 | 116323 | 1554.15 | 0.149203 | 2.18905 | 1(Win) | true |
| Jsonifier (two-stage) | 1079.88 | 0.293978 | 164.319ms | 1811 | 4890 | 108099 | 1599.35 | 0.0262552 | 2.25377 | 2(Loss) | true |
| Glaze | 503.529 | 0.213936 | 357.614ms | 1811 | 40 | 2153.85 | 3430 | 0.0972763 | 4.87624 | 3(Loss) | true |
| simdjson (ondemand) | 357.075 | 0.187686 | 507.551ms | 1811 | 4890 | 402985 | 4836.81 | 0.106986 | 6.89195 | 4(Loss) | true |
