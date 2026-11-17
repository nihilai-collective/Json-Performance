
----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 33895.3 | 0.0774446 | 90.991ms | 31235 | 80 | 37.0576 | 878.825 | 0.116769 | 0.070844 | 1(Win) | true |
| Glaze | 6455.68 | 0.0997569 | 472.572ms | 31235 | 30 | 635.633 | 4614.23 | 0.130202 | 0.381482 | 2(Loss) | true |
| simdjson (reflection) | 559.189 | 0.143808 | 5178.75ms | 31235 | 320 | 1.87793e+06 | 53270 | 0.544072 | 4.42531 | 3(Loss) | true |
