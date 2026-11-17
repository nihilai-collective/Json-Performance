
----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11624.5 | 0.228888 | 827.86ms | 9578 | 2560 | 8281.12 | 785.78 | 0.396876 | 0.463765 | 1.88557 | 0.21539 | 0.000822768 | 1.99024e-05 | 8.48298e-06 | 1(Win) | true |
| Glaze | 4540.91 | 0.0517092 | 950.799ms | 9578 | 4890 | 5290.63 | 2011.55 | 0.0567063 | 1.14695 | 4.99374 | 0.731781 | 0.000216071 | 3.25601e-05 | 1.01844e-05 | 2(Loss) | true |
