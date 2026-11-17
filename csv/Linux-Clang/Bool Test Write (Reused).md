
----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4259.48 | 0.221572 | 743.597ms | 905 | 4890 | 985.646 | 202.625 | 0.114803 | 1.44764 | 5.79779 | 0.272929 | 0.0022165 | 7.41168e-05 | 2.21446e-05 | 1(Win) | true |
| Glaze | 902.859 | 0.25114 | 826.922ms | 905 | 640 | 3688.65 | 955.936 | 0.0341732 | 5.87234 | 24.0597 | 3.14917 | 0.00121547 | 8.6326e-05 | 1.72652e-05 | 2(Loss) | true |
