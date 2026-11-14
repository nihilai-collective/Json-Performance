
----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2619.21 | 0.413149 | 174.286ms | 4669 | 4890 | 241229 | 1700.02 | 0.29013 | 1(Win) | true |
| Jsonifier (two-stage) | 1613.65 | 0.512217 | 280.122ms | 4669 | 1280 | 255710 | 2759.4 | 0.741007 | 2(Loss) | true |
| simdjson (reflection) | 1186.91 | 0.342563 | 371.451ms | 4669 | 2560 | 422797 | 3751.5 | 1.30975 | 3(Loss) | true |
| Glaze | 1155.08 | 0.574683 | 398.817ms | 4669 | 2560 | 1.25638e+06 | 3854.9 | 0.697456 | 4(Loss) | true |
| simdjson (ondemand) | 1072.28 | 0.161612 | 420.073ms | 4669 | 4890 | 220234 | 4152.54 | 0.237523 | 5(Loss) | true |
