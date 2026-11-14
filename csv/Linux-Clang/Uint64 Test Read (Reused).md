
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 738.271 | 0.0850953 | 500.156ms | 3873 | 80 | 1449.99 | 5003.01 | 0.0746492 | 3.33514 | 1(Win) | true |
| simdjson (ondemand) | 614.508 | 0.108383 | 601.663ms | 3873 | 4890 | 207526 | 6010.63 | 0.0982797 | 4.01048 | 2(Loss) | true |
