
----
### Instruments Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2104 | 0.0766368 | 5127.55ms | 108313 | 1280 | 1.81198e+06 | 49094.6 | 0.0124265 | 1.17609 | 1(Win) | true |
| simdjson (ondemand) | 1834.6 | 0.0548935 | 5836.37ms | 108313 | 2560 | 2.44547e+06 | 56304.1 | 0.0225926 | 1.3489 | 2(Loss) | true |
