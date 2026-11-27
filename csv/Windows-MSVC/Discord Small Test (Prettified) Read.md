
----
### Discord Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1099.25 | 0.0844823 | 584.212ms | 6701 | 2560 | 61753.4 | 5813.59 | 0.139954 | 2.75424 | 1(Win) | true |
| simdjson (ondemand) | 1019.14 | 0.0584344 | 633.334ms | 6701 | 4890 | 65653.4 | 6270.55 | 0.0758584 | 2.97201 | 2(Loss) | true |
