
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1685.89 | 0.070807 | 221.902ms | 3873 | 4890 | 11767.9 | 2190.88 | 0.178847 | 1.78618 | 1(Win) | true |
| Glaze | 1015.77 | 0.14874 | 367.485ms | 3873 | 80 | 2340.19 | 3636.25 | 0.172176 | 2.97535 | 2(Loss) | true |
| Jsonifier (two-stage) | 916.382 | 0.0628228 | 405.526ms | 3873 | 4890 | 31353.5 | 4030.61 | 0.192773 | 3.2981 | 3(Loss) | true |
| simdjson (ondemand) | 457.883 | 0.0528509 | 812.581ms | 3873 | 4890 | 88879.1 | 8066.65 | 0.0163924 | 6.6206 | 4(Loss) | true |
