#pragma once
#ifndef CATOOL_DIAGNOSTICTOOLBOX_DIAGNOSTICENGINE_H
#define CATOOL_DIAGNOSTICTOOLBOX_DIAGNOSTICENGINE_H

#include<memory>
namespace catool
{
	namespace diagnostic_toolbox
	{
		class DiagnosticConsumer
		{
		protected:
			unsigned NumWarnings = 0;
			unsigned NumErrors = 0;
		public:
			DiagnosticConsumer() = default;
			virtual ~DiagnosticConsumer()=default;
			unsigned getNumErrors() const { return NumErrors; }
			unsigned getNumWarnings() const { return NumWarnings; }
			virtual void clear() { NumWarnings = NumErrors = 0; }
		};
		class DiagnosticIDs
		{
		public:

		};
		class DiagnosticOptions
		{
		public:

		};
		class DiagnosticEngine
		{
		private:
			bool SuppressAfterFatalError;  // Suppress diagnostics after a fatal error?
			bool SuppressAllDiagnostics;   // Suppress all diagnostics.

			bool ShowColors;               // Color printing is enabled.

			unsigned ErrorLimit;           // Cap of # errors emitted, 0 -> no limit.
			DiagnosticIDs Diags;
			DiagnosticOptions DiagOpts;
			DiagnosticConsumer *Client;
			std::unique_ptr<DiagnosticConsumer> Owner;
		public:

		};
	}
}
#endif // !CATOOL_DIAGNOSTICTOOLBOX_DIAGNOSTICENGINE_H