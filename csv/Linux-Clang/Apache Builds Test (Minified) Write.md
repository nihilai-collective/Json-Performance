
----
### Apache Builds Test (Minified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15561.4 | 0.190918 | 1317.27ms | 94653 | 320 | 39247.8 | 5800.77 | 0.0925743 | 0.326819 | 1.29682 | 0.184104 | 8.36278e-05 | 5.84371e-06 | 3.07043e-06 | 1(Win) | true |
| Glaze | 5288.9 | 0.072527 | 2433.4ms | 94653 | 2560 | 392263 | 17067.5 | 0.360831 | 0.955656 | 4.37683 | 0.66691 | 9.17702e-05 | 1.50385e-05 | 1.00862e-05 | 2(Loss) | true |
