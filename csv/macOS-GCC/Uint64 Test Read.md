
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1215.39 | 0.956673 | 96.4239ms | 1213 | 1280 | 106128 | 951.8 | 1.04034 | 1(Win) | true |
| Glaze | 856.387 | 0.72125 | 139.313ms | 1213 | 2560 | 242993 | 1350.8 | 0.670741 | 2(Loss) | true |
| simdjson (reflection) | 730.215 | 0.889255 | 160.204ms | 1213 | 1280 | 254029 | 1584.2 | 0.215081 | 3(Loss) | true |
| simdjson (ondemand) | 293.695 | 0.184005 | 396.621ms | 1213 | 2560 | 134470 | 3938.8 | 0.116923 | 4(Loss) | true |
