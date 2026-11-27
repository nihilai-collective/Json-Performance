
----
### Discord Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 852.174 | 0.104391 | 801.819ms | 6701 | 1280 | 78443.4 | 7499.14 | 0.00312546 | 3.55759 | 1(Win) | true |
| simdjson (ondemand) | 263.722 | 0.0742819 | 2464.44ms | 6701 | 1280 | 414728 | 24232.3 | 0.107244 | 11.5169 | 2(Loss) | true |
