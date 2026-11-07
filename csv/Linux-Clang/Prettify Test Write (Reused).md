
----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6016.36 | 0.205065 | 5816.03ms | 699405 | 80 | 4.13488e+06 | 110865 | 0.135656 | 0.411399 | 1(Win) | true |
| Glaze | 3791.48 | 0.0926904 | 9406.63ms | 699405 | 320 | 8.50865e+06 | 175922 | 0.286866 | 0.652895 | 2(Loss) | true |
| simdjson (ondemand) | 2562.8 | 0.145176 | 7583.36ms | 767297 | 80 | 1.3746e+07 | 285528 | 0.0656277 | 0.965665 | 3(Loss) | true |
