
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 923.659 | 0.129107 | 414.043ms | 3862 | 80 | 2120.25 | 3987.5 | 1.23839 | 3.2638 | 1(Win) | true |
| simdjson (ondemand) | 605.771 | 0.0740189 | 620.734ms | 3862 | 80 | 1620.25 | 6080 | 0.620604 | 4.98892 | 2(Loss) | true |
