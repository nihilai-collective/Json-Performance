
----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 460.671 | 0.141447 | 805.287ms | 3873 | 4890 | 628939 | 8017.83 | 0.271357 | 5.34442 | 1(Win) | true |
| Glaze | 342.449 | 0.361155 | 1106.88ms | 3873 | 640 | 971112 | 10785.8 | 0.0913494 | 7.20746 | 2(Loss) | true |
