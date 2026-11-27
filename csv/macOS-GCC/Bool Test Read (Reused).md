
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1778.82 | 1.48093 | 51.7888ms | 905 | 4890 | 252471 | 485.196 | 1.06143 | 1(Win) | true |
| Glaze | 1459.87 | 4.69171 | 60.33ms | 905 | 320 | 246196 | 591.2 | 0.407609 | 2(Loss) | true |
| simdjson (reflection) | 813.608 | 1.26898 | 101.31ms | 905 | 640 | 115973 | 1060.8 | 3.27103 | 3(Loss) | true |
| simdjson (ondemand) | 353.506 | 0.420952 | 238.498ms | 905 | 4890 | 516511 | 2441.48 | 1.76632 | 4(Loss) | true |
