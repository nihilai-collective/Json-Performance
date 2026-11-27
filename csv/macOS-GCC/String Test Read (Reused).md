
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1814.31 | 0.291496 | 322.292ms | 4215 | 4890 | 203962 | 2215.58 | 0.463726 | 1(Win) | true |
| simdjson (reflection) | 1015.09 | 0.232148 | 492.093ms | 4215 | 640 | 54087.7 | 3960 | 0.202429 | 2(Loss) | true |
| Glaze | 980.232 | 0.192406 | 511.619ms | 4215 | 2560 | 159374 | 4100.8 | 0.687785 | 3(Loss) | true |
| simdjson (ondemand) | 672.557 | 0.447147 | 692.235ms | 4215 | 320 | 228554 | 5976.8 | 0.0937835 | 4(Loss) | true |
