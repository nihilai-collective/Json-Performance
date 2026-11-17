
----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1607.15 | 0.43281 | 272.409ms | 4390 | 2560 | 325424 | 2605 | 0.0920457 | 1(Win) | true |
| Jsonifier (two-stage) | 1179.2 | 1.14922 | 372.143ms | 4390 | 160 | 266366 | 3550.4 | 0.316456 | 2(Loss) | true |
| Glaze | 960.501 | 0.603114 | 443.192ms | 4390 | 640 | 442296 | 4358.8 | 0.0642792 | 3(Loss) | true |
| simdjson (reflection) | 944.627 | 0.201031 | 453.915ms | 4390 | 4890 | 388188 | 4432.05 | 0.0958951 | 4(Loss) | true |
| simdjson (ondemand) | 669.338 | 0.369676 | 631.519ms | 4390 | 4890 | 2.6145e+06 | 6254.88 | 1.26782 | 5(Loss) | true |
