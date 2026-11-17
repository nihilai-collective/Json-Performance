
----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 19972.7 | 0.040401 | 1253.89ms | 108313 | 2560 | 11176.6 | 5171.82 | 0.0415919 | 0.254859 | 1.0938 | 0.288839 | 0.000109405 | 3.83005e-06 | 9.30463e-07 | 1(Win) | true |
| simdjson (reflection) | 15058.3 | 0.0868495 | 1425.75ms | 108313 | 640 | 22715.5 | 6859.67 | 0.00350794 | 0.337434 | 1.49385 | 0.193716 | 0.000175547 | 6.3762e-06 | 3.1304e-06 | 2(Loss) | true |
| Glaze | 5611.05 | 0.242142 | 2591.83ms | 108313 | 320 | 635862 | 18409.3 | 0.0115954 | 0.899603 | 3.01787 | 0.397404 | 0.000286438 | 8.68432e-06 | 5.33754e-06 | 3(Loss) | true |
