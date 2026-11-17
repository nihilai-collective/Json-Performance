
----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13421.3 | 0.0333866 | 8194.64ms | 2251027 | 2560 | 7.30061e+06 | 159951 | 0.0693319 | 0.226326 | 1(Win) | true |
| simdjson (stage-1) | 10654.2 | 0.166968 | 5153.02ms | 2251027 | 40 | 4.52738e+06 | 201492 | 0.00620409 | 0.28515 | 2(Loss) | true |
