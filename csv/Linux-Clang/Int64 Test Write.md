
----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 817.179 | 0.340567 | 491.793ms | 3862 | 1280 | 301582 | 4507.08 | 0.233876 | 3.01082 | 1(Win) | true |
| Glaze | 768.684 | 0.09373 | 483.394ms | 3862 | 40 | 806.763 | 4791.43 | 0.130089 | 3.20203 | 2(Loss) | true |
