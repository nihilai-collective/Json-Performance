
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1817.77 | 2.0907 | 50.985ms | 905 | 2560 | 252257 | 474.8 | 0.978307 | 1(Win) | true |
| Glaze | 1601.25 | 1.84014 | 59.66ms | 905 | 2560 | 251837 | 539 | 0.22214 | 2(Loss) | true |
| Jsonifier (two-stage) | 344.899 | 3.3066 | 256.519ms | 905 | 40 | 273865 | 2502.4 | 0.0853242 | 3(Loss) | true |
| simdjson (ondemand) | 154.402 | 0.350695 | 537.347ms | 905 | 4890 | 1.87915e+06 | 5589.8 | 1.06541 | 4(Loss) | true |
