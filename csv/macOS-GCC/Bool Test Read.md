
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 1851.3 | 2.17568 | 47.85ms | 905 | 2560 | 263375 | 466.2 | 6.97568 | -(Win) | false |
| Glaze | 1482.69 | 1.68626 | 64.3489ms | 905 | 2560 | 246651 | 582.1 | 1.6723 | 2(Loss) | true |
| simdjson (reflection) | 902.421 | 0.854585 | 101.752ms | 905 | 1280 | 85506.6 | 956.4 | 2.28852 | 3(Loss) | true |
| simdjson (ondemand) | 426.378 | 0.846015 | 229.253ms | 905 | 1280 | 375381 | 2024.2 | 0.606362 | 4(Loss) | true |
