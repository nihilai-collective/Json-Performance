
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1717.96 | 0.242422 | 217.232ms | 3873 | 4890 | 132838 | 2149.98 | 0.212072 | 1.42267 | 1(Win) | true |
| Glaze | 1151.55 | 0.131493 | 333.318ms | 3873 | 40 | 711.538 | 3207.5 | 0.0259875 | 2.13225 | 2(Loss) | true |
| Jsonifier (two-stage) | 592.439 | 0.351113 | 631.973ms | 3873 | 640 | 306677 | 6234.53 | 0.122653 | 4.16198 | 3(Loss) | true |
| simdjson (ondemand) | 313.836 | 0.125473 | 1183.85ms | 3873 | 4890 | 1.06635e+06 | 11769.1 | 0.326668 | 7.87059 | 4(Loss) | true |
