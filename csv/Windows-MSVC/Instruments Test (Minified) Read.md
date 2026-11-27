
----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1082.91 | 0.115789 | 9533.02ms | 108313 | 4890 | 5.96509e+07 | 95386.4 | 0.125346 | 2.80591 | 1(Win) | true |
| simdjson (ondemand) | 892.844 | 0.217358 | 6013.51ms | 108313 | 40 | 2.52943e+06 | 115692 | 0.0554324 | 3.40371 | 2(Loss) | true |
