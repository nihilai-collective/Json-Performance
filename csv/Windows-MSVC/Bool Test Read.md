
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 502.336 | 0.35025 | 176.523ms | 905 | 640 | 23176.4 | 1718.12 | 0.218739 | 4.84824 | 1(Win) | true |
| Glaze | 451.429 | 0.0975232 | 200.625ms | 905 | 320 | 1112.46 | 1911.88 | 0.325839 | 5.40416 | 2(Loss) | true |
| simdjson (ondemand) | 152.281 | 0.313122 | 579.639ms | 905 | 1280 | 403128 | 5667.66 | 0.0910596 | 16.1464 | 3(Loss) | true |
