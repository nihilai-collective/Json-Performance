
----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 716.635 | 0.515828 | 566.403ms | 4215 | 1280 | 1.07157e+06 | 5609.18 | 1.03578 | 1(Win) | true |
| Glaze | 434.02 | 0.670822 | 928.679ms | 4215 | 640 | 2.47042e+06 | 9261.64 | 1.22964 | 2(Loss) | true |
