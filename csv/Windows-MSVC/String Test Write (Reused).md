
----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8248.83 | 0.143697 | 125.562ms | 9578 | 640 | 1620.48 | 1107.34 | 0.211208 | 0.293227 | 1(Win) | true |
| Glaze | 2651.46 | 0.162474 | 373.946ms | 9578 | 80 | 2506.33 | 3445 | 0.0726216 | 0.924777 | 2(Loss) | true |
