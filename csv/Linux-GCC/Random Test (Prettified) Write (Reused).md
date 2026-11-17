
----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 24902.9 | 0.0922162 | 3200.54ms | 837491 | 4890 | 4.27744e+06 | 32072.3 | 0.0341087 | 0.0993193 | 1(Win) | true |
| Glaze | 4164.08 | 0.325486 | 9638.81ms | 837491 | 40 | 1.559e+07 | 191805 | 0.819821 | 0.594487 | 2(Loss) | true |
| simdjson (reflection) | 581.273 | 0.127131 | 9013.11ms | 837491 | 30 | 9.1542e+07 | 1.37404e+06 | 0.111168 | 4.25923 | 3(Loss) | true |
