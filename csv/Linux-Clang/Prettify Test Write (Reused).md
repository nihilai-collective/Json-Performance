
----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4606.01 | 0.059905 | 7778.97ms | 699405 | 1280 | 9.6326e+06 | 144812 | 0.0219719 | 1.08753 | 4.43374 | 0.719304 | 0.00285298 | 0.0011256 | 1.16729e-06 | 1(Win) | true |
| Glaze | 3514.3 | 0.176125 | 5043.57ms | 699405 | 80 | 8.93949e+06 | 189797 | 0.023333 | 1.43087 | 5.2208 | 1.16228 | 0.00221494 | 0.00109557 | 1.68536e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2281.98 | 0.264997 | 8385.99ms | 767297 | 80 | 5.77665e+07 | 320666 | 0.152656 | 2.18903 | 8.67078 | 1.18229 | 0.00370807 | 0.0927822 | 1.35215e-05 | 3(Loss) | true |
