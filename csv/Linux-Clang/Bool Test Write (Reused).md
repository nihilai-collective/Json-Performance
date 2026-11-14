
----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4599.26 | 0.201638 | 756.243ms | 905 | 4890 | 700.123 | 187.655 | 0.288949 | 1.34893 | 5.79779 | 0.272929 | 0.00221446 | 3.977e-05 | 9.94249e-06 | 1(Win) | true |
| Glaze | 881.641 | 0.105816 | 839.601ms | 905 | 4890 | 5247.22 | 978.942 | 0.101973 | 6.0178 | 24.0597 | 3.14917 | 0.0013106 | 0.000188681 | 9.64874e-05 | 2(Loss) | true |
