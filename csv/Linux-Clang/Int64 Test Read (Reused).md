
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 923.566 | 0.203175 | 409.626ms | 3862 | 30 | 1969.47 | 3987.9 | 0.101037 | 2.66347 | 1(Win) | true |
| simdjson (ondemand) | 673.43 | 0.234701 | 551.528ms | 3862 | 1280 | 210901 | 5469.15 | 0.00221417 | 3.65843 | 2(Loss) | true |
