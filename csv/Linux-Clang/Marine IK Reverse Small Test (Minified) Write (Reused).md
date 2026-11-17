
----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1519.91 | 0.322539 | 1027.09ms | 4604 | 320 | 27781.3 | 2888.81 | 0.0149261 | 3.389 | 9.23653 | 0.631408 | 0.000498887 | 2.85078e-05 | 1.22176e-05 | 1(Win) | true |
| Glaze | 855.281 | 0.075424 | 1255.2ms | 4604 | 2560 | 38380.6 | 5133.65 | 0.00849865 | 5.96392 | 12.4472 | 0.970678 | 0.000890191 | 0.00014466 | 7.1015e-05 | 2(Loss) | true |
