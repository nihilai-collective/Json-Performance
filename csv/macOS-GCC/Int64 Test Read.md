
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2395.31 | 0.482809 | 159.969ms | 3862 | 4890 | 269501 | 1537.62 | 0.485094 | 1(Win) | true |
| Glaze | 1133.83 | 0.418309 | 295.495ms | 3862 | 4890 | 902891 | 3248.37 | 0.0515294 | 2(Loss) | true |
| Jsonifier (two-stage) | 830.741 | 0.430118 | 452.882ms | 3862 | 2560 | 930912 | 4433.5 | 1.60023 | 3(Loss) | true |
| simdjson (ondemand) | 406.421 | 0.211946 | 879.324ms | 3862 | 4890 | 1.80398e+06 | 9062.24 | 0.31374 | 4(Loss) | true |
