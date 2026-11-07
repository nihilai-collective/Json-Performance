
----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2359.26 | 0.12303 | 1079.77ms | 25388 | 80 | 12753.2 | 10262.5 | 0.0975372 | 1.04463 | 1(Win) | true |
| Jsonifier | 2310.99 | 0.13781 | 1102.28ms | 25388 | 4890 | 1.01937e+06 | 10476.9 | 0.0658093 | 1.06668 | 2(Loss) | true |
| Glaze | 1523.96 | 0.295732 | 1654.9ms | 25388 | 40 | 88301.3 | 15887.5 | 0.036703 | 1.61944 | 3(Loss) | true |
| simdjson (ondemand) | 1163.78 | 0.109254 | 2120.63ms | 25388 | 4890 | 2.52638e+06 | 20804.5 | 0.315055 | 2.12288 | 4(Loss) | true |
